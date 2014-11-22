#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <boost/asio.hpp>
#include <iostream>

#include "tcp_connection.h"

class tcp_server
{
    public:
        tcp_server(boost::asio::io_service& io_service, int port);
        virtual ~tcp_server();
    protected:
    private:
        void start_accept();
        void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);

        boost::asio::ip::tcp::acceptor m_acceptor;
};

#endif // TCP_SERVER_H
