#include <boost/asio.hpp>
#include <iostream>

#include "tcp_server.h"

int main()
{
	try
	{
		boost::asio::io_service io_service;

		tcp_server server(io_service, 7171);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
