#include "Room.h"

Room::Room(/*Server& server*/) :
    // m_server(server),
    m_playerCounter(0)
{
    m_world = new StaticWorld("scenario1", "data");
    std::cout << "New room" << std::endl;
}

Room::~Room()
{
    delete m_world;
}

void Room::join(Session::chat_session_ptr participant)
{
    const ZoneLinker::ZoneLink *startLink = m_world->getArea(m_world->getStartArea())->getLinker()->find("start");
    if (NULL == startLink)
    {
        /** @todo throw Exception */
    }

    participant->getPlayer().m_number = ++m_playerCounter;
    participant->getPlayer().m_zone = startLink->zone;
    participant->getPlayer().m_tile = startLink->tile;

    m_participants.insert(participant);
    DownMessage e;
    e.m_type = DownMessage::WELCOME;
    e.m_players.push_back(participant->getPlayer());
    participant->deliver(e);

    e.reset();
    e.m_type = DownMessage::PLAYER_CONNECTED;
    e.m_info = "New player entered";

    deliver(e);
}

void Room::leave(Session::chat_session_ptr participant)
{
    // On informe les sessions de la room // (2)
    DownMessage e;
    e.m_type = DownMessage::PLAYER_LEFT;
    e.m_info = "A player left";
    deliver(e);

    m_participants.erase(participant);// puis on le détruit
}

void Room::deliver(DownMessage& msg)
{
    std::for_each(m_participants.begin(), m_participants.end(),
                  boost::bind(&Session::deliver, _1, boost::ref(msg)));
}

void Room::broadcast()
{
    DownMessage msg;
    msg.m_type = DownMessage::WORLD_STATE;
    for (std::set<chat_session_ptr>::iterator it = m_participants.begin(); m_participants.end() != it; it++)
    {
        msg.m_players.push_back((**it).getPlayer());
    }

    deliver(msg);
}

StaticWorld* Room::getWorld() const
{
    return m_world;
}
