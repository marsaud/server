#include "Room.h"

Room::Room(/*Server& server*/)
// :m_server(server)
{
	std::cout << "New room" << std::endl;
}

Room::~Room()
{
    //dtor
}

void Room::join(Session::chat_session_ptr participant)
{
	m_participants.insert(participant);

    /** @todo Handle player arrival */

	DownMessage e;
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

void Room::deliver(const DownMessage& msg)
{
	std::for_each(m_participants.begin(), m_participants.end(),
		boost::bind(&Session::deliver, _1, boost::ref(msg)));
}
