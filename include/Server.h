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
    Server(boost::asio::io_service& io_service, int port);
    virtual ~Server();

protected:
private:
    void wait_for_connection();
    void handle_accept(Connection::connection_ptr connection, const boost::system::error_code& error);
    void m_drive_broadcast();
    void m_broadcast();

    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::shared_ptr<Room> m_room;
    boost::asio::deadline_timer m_timer;

};

#endif // SERVER_H
