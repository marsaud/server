#include "Server.h"

Server::Server(boost::asio::io_service& io_service, int port) :
    m_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    m_room(new Room())
{
    std::cout << "Server start" << std::endl;
    wait_for_connection();
}

Server::~Server()
{
    //dtor
}

// Attente d'un nouveau client
void Server::wait_for_connection()
{
    Connection::connection_ptr connection = Connection::create(m_acceptor.get_io_service());
// Attente d'une nouvelle connexion
    m_acceptor.async_accept(
        connection->socket(),
        boost::bind(
            &Server::handle_accept,
            this,
            connection,
            boost::asio::placeholders::error
        )
    );

    std::cout << "Listening" << std::endl;
}

void Server::handle_accept(Connection::connection_ptr connection, const boost::system::error_code& error)
{
    std::cerr << error.message() << std::endl;

    if (!error)
    {
        std::cout << "Connection accepted " << std::endl;

        /** @todo la room est injectée dans la session, mais la session doit être repassée à le room pour le join...creuser ça. */
        chat_session_ptr session = Session::create(connection, m_room);
        m_room->join(session);
        wait_for_connection();
    }
    else
    {
        std::cerr << "Connection rejected : " << error.message() << std::endl;
    }
}
