#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    tcp_connection();
    virtual ~tcp_connection();

    static pointer create(boost::asio::io_service& ios);
    boost::asio::ip::tcp::socket& socket();
    void start();
protected:
private:
    tcp_connection(boost::asio::io_service& io_service);
    void handle_write(const boost::system::error_code& error);

    boost::asio::ip::tcp::socket m_socket;
    std::string m_message;
};

#endif // TCP_CONNECTION_H
