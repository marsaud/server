#include "Server.h"

Server::Server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint) : m_io_service(io_service),
    m_acceptor(io_service, endpoint),
    m_room(new Room(/* *this*/))
{
    std::cout << "Creation d'un serveur " << std::endl;

    wait_for_connection();
}

Server::~Server()
{
    //dtor
}

// Attente d'un nouveau client
void Server::wait_for_connection()
{
    connection_ptr connection(new Connection(m_io_service));

    // Attente d'une nouvelle connection
    m_acceptor.async_accept(connection->socket(),
                            boost::bind(&Server::handle_accept, this,
                                        boost::asio::placeholders::error,
                                        connection)
                           );
}

void Server::handle_accept(const boost::system::error_code& error, connection_ptr connection)
{
    if (!error)
    {
        std::cout << "Connection acceptée " << std::endl;

        /** @todo la room est injectée dans la session, mais la session doit être repassée à le room pour le join...creuser ça. */
        chat_session_ptr session = Session::create(connection, m_room);
        m_room->join(session);
        wait_for_connection();
    }
    else
    {
        std::cerr << "Connection refusée : " << error.message() << std::endl;
    }
}
