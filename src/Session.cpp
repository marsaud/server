#include "Session.h"

Session::Session(connection_ptr tcp_connection, chat_room_ptr room)
: m_tcp_connection(tcp_connection),
m_room(room)
{
	is_leaving = false;
	std::cout << "New session ! "  << std::endl;
}

Session::~Session()
{
    std::cout << "Session détruite" << std::endl;
}

void Session::wait_for_data()
{
	// On lance l'écoute d'événements
	m_tcp_connection->async_read(m_message,
		boost::bind(&Session::handle_read, shared_from_this(),
		boost::asio::placeholders::error)
		);
}

void Session::handle_read(const boost::system::error_code &error)
{
	chat_room_ptr room = m_room.lock();
	if (room)
	{
		if (!error)
		{
			// On demande à la room de transmettre le message à tout le monde
			room->deliver(m_message);

            /** @todo Ici, on traiter le message entrant, modifier le modèle,
             * puis rediffuser le modèle à jour à tous les clients
             */

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

void Session::deliver(const UpMessage& msg)
{
	m_tcp_connection->async_write(msg,
		boost::bind(&Session::handle_write, shared_from_this(),
		boost::asio::placeholders::error)
		);
}

void Session::handle_write(const boost::system::error_code &error)
{
	chat_room_ptr room = m_room.lock();
	if (room && error && (!is_leaving) )
	{
		is_leaving = true;
		room->leave(shared_from_this() );
	}
}
