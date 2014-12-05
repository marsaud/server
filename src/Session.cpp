#include "Session.h"

Session::Session(Connection::connection_ptr tcp_connection, chat_room_ptr room)
    : m_tcp_connection(tcp_connection),
      m_room(room)
{
    is_leaving = false;

    chat_room_ptr pRoom = m_room.lock();
    m_player.m_area = pRoom->getWorld()->getStartArea();

    const ZoneLinker::ZoneLink* startLink = pRoom->getWorld()->getArea(m_player.m_area)->getLinker()->find("start");
    if (NULL == startLink)
    {
        /** @todo throw Exception */
        std::cerr << "No start link found"  << std::endl;
    }

    m_player.m_zone = startLink->zone;
    m_player.m_tile = startLink->tile;


    std::cout << "New session"  << std::endl;
}

Session::~Session()
{
    std::cout << "Session destroyed" << std::endl;
}

void Session::wait_for_data()
{
    // On lance l'écoute d'événements
    m_tcp_connection->async_read(
        m_upMessage,
        boost::bind(
            &Session::handle_read,
            shared_from_this(),
            boost::asio::placeholders::error
        )
    );
}

void Session::handle_read(const boost::system::error_code &error)
{
    chat_room_ptr room = m_room.lock();
    if (room)
    {
        if (!error)
        {
            MovementProcessor::move(m_upMessage.m_move, m_player, room->getWorld());
            ActionProcessor::process(m_upMessage.m_action, m_player, room->getWorld());

            /** @todo Ici, on traiter le message entrant, modifier le modèle,
             * puis rediffuser le modèle à jour à tous les clients
             */

            m_DownMessage.reset();
            m_DownMessage.m_type = DownMessage::WORLD_STATE;

            // On demande à la room de transmettre le message à tout le monde
            room->deliver(m_DownMessage);

            // On relance une écoute
            wait_for_data();
        }

        else
        {
            if (!is_leaving)
            {
                is_leaving = true;
                room->leave(shared_from_this() );
            }
        }
    }
}

void Session::deliver(const DownMessage& msg)
{
    m_tcp_connection->async_write(msg,
                                  boost::bind(&Session::handle_write, shared_from_this(),
                                          boost::asio::placeholders::error)
                                 );
}

Player& Session::getPlayer()
{
    return m_player;
}

void Session::handle_write(const boost::system::error_code &error)
{
    chat_room_ptr room = m_room.lock();
    if (room && error && (!is_leaving))
    {
        is_leaving = true;
        room->leave(shared_from_this() );
    }
}

chat_session_ptr Session::create(Connection::connection_ptr tcp_connection, chat_room_ptr room)
{
    chat_session_ptr session(new Session(tcp_connection, room));
    session->wait_for_data();
    return session;
}
