#include <iostream>

#include <boost/asio.hpp>

#include "Server.h"

int main()
{
	try
	{
		boost::asio::io_service io_service;

		Server server(io_service, 7171);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
