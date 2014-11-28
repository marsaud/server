#include <iostream>

#include <boost/asio.hpp>

#include "Server.h"

int main()
{
	try
	{
		boost::asio::io_service io_service;

		Server server(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 7171));
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
