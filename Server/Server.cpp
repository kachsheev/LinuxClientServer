#include <cstring>
#include <iostream>
#include "Server.hpp"

Server::Server(int argc, char **argv)
{
	if(validArguments(argc, argv))
	{
		// base server setting
		parseArguments(argc, argv);
	}
	else
	{
		// make invalid
	}
}

Server::~Server()
{
	// if valid - do something
}

bool Server::start()
{
	using std::cin;
	using std::cout;
	using std::string;

	bool working = true;
	if (!connection.connect())
	{
		return false;
	}

	while (working)
	{
		cout << "-> "; cin >> msg;
		switch (connection.getProtocol())
		{
			case Connection::Protocol::UDP:
			{
				udpProcess();
				break;
			}
			case Connection::Protocol::TCP:
			{
				tcpProcess();
				break;
			}
		}
	}
	return true;
}

void Server::udpProcess(const std::string &/*message*/)
{
}

void Server::tcpProcess(const std::string &/*message*/)
{
}

void Server::printUsage()
{
	using std::cout;
	cout << "Options:\n";
	cout << "\t" "-t   --proto   <TCP/UDP>" "\n"
			"\t" "-p   --port    <port number>" "\n";
	cout.flush();
}

bool Server::validArguments(int argc, char **argv)
{
	using std::cout;

	if (argc != 5)
	{
		goto fail;
	}
	else
	{
		for (int i = 1; i < argc; i += 2)
		{
			if (!strcmp("-t", argv[i]) && !strcmp("--proto", argv[i]))
			{
				goto fail;
			} else if (!strcmp("-p", argv[i]) && !strcmp("--port", argv[i]))
			{
				goto fail;
			}
		}
	}
	return true;

fail:
	cout << argv[0] << " <options>" "\n";
	printUsage();
	return false;
}

void Server::parseArguments(int argc, char **argv)
{
	using std::strcmp;

	const char *strProtocol = nullptr;
	const char *strPort = nullptr;
	for (int i = 1; i < argc; ++i)
	{
		if (strcmp("-t", argv[i]) || strcmp("--proto", argv[i]))
		{
			strProtocol = argv[i+1];
			++i;
		}
		else if (strcmp("-p", argv[i]) || strcmp("--port", argv[i]))
		{
			strPort = argv[i+1];
			++i;
		}
	}
	connection = ServerConnection(strProtocol, strPort);
}
