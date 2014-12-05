#ifndef SESSION_H
#define SESSION_H

#include <iostream>

#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

#include "Connection.h"
#include "UpMessage.h"
#include "DownMessage.h"
#include "Room.h"
#include "MovementProcessor.h"
#include "ActionProcessor.h"
#include "Player.h"
#include "ZoneLinker.h"

class Room;

class Session : public boost::enable_shared_from_this<Session>
{
public:
    virtual ~Session();

    typedef boost::shared_ptr<Session> chat_session_ptr;
    typedef boost::shared_ptr<Room> chat_room_ptr;
    typedef boost::weak_ptr<Room> chat_room_wptr;

    static chat_session_ptr create(Connection::connection_ptr tcp_connection, chat_room_ptr room);

    void deliver(const DownMessage& msg);
    Player& getPlayer();

protected:
private:
    Session(Connection::connection_ptr tcp_connection, chat_room_ptr room);
    void wait_for_data();

    void handle_write(const boost::system::error_code& error);
    void handle_read(const boost::system::error_code& error);

    Connection::connection_ptr m_tcp_connection;
    chat_room_wptr m_room;

    Player m_player;

    UpMessage m_upMessage;
    DownMessage m_DownMessage;

    bool is_leaving;
};

#endif // SESSION_H
