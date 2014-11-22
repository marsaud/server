#include "tcp_connection.h"

tcp_connection::tcp_connection(boost::asio::io_service& io_service)
    : m_socket(io_service)
{
    //ctor
}

tcp_connection::~tcp_connection()
{
    //dtor
}

tcp_connection::pointer tcp_connection::create(boost::asio::io_service& ios)
{
    return pointer(new tcp_connection(ios));
}

boost::asio::ip::tcp::socket& tcp_connection::socket()
{
    return m_socket;
}

void tcp_connection::start()
{
    m_message = "Bienvenue sur le serveur!";

    boost::asio::async_write(m_socket,
                             boost::asio::buffer(m_message),
                             boost::bind(&tcp_connection::handle_write,
                                         shared_from_this(),
                                         boost::asio::placeholders::error));
}

void tcp_connection::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
        // Autres actions éventuelles
    }
}

