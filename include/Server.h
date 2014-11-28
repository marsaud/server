#ifndef SERVER_H
#define SERVER_H

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Session.h"
#include "Connection.h"
#include "Room.h"

class Server
{
public:
    Server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);
    virtual ~Server();

    typedef boost::shared_ptr<Room> chat_room_ptr;

    void wait_for_connection();
protected:
private:
    void handle_accept(const boost::system::error_code& error, connection_ptr);

    boost::asio::io_service& m_io_service;
    boost::asio::ip::tcp::acceptor m_acceptor;
    chat_room_ptr m_room;
};

#endif // SERVER_H
