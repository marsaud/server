#ifndef ROOM_H
#define ROOM_H

#include <iostream>

#include <boost/enable_shared_from_this.hpp>

#include "StaticWorld.h"
#include "UpMessage.h"
#include "Session.h"

class Session;
typedef boost::shared_ptr<Session> chat_session_ptr;

class Room
{
public:
    Room(/*Server& server*/);
    virtual ~Room();

    void join(chat_session_ptr participant);
    void leave(chat_session_ptr participant);
    void deliver(DownMessage& msg);
    StaticWorld* getWorld() const;

protected:
private:
    std::set<chat_session_ptr>	m_participants;
    // Server& m_server;

    StaticWorld* m_world;
};

#endif // ROOM_H
