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

	// On informe les sessions de la room
	UpMessage e;
	e.m_type = UpMessage::PERSON_CONNECTED;
	deliver(e);
}

void Room::leave(Session::chat_session_ptr participant)
{
	// On informe les sessions de la room // (2)
	UpMessage e;
	e.m_type = UpMessage::PERSON_LEFT;
	deliver(e);

	m_participants.erase(participant);// puis on le détruit
}

void Room::deliver(const UpMessage& msg)
{
	std::for_each(m_participants.begin(), m_participants.end(),
		boost::bind(&Session::deliver, _1, boost::ref(msg)));
}
