#include <cstring>
#include <iostream>
#include "Server.hpp"

Server::Server(int argc, char **argv) : connection(nullptr)
{
	if(validAndParseArguments(argc, argv))
	{
		// base server setting
		printed = false;
	}
	else
	{
		// make invalid
		printed = true;
	}
}

Server::~Server()
{
	delete connection;
}

bool Server::start()
{
	using std::cin;
	using std::cerr;
	using std::cout;
	using std::string;

	bool working = true;
	Message message;

	if (printed)
	{
		goto exitLabel;
	}

	if (connection->getProtocol() == Connection::Protocol::UNKNOWN)
	{
		cerr << "Server::start(): unknown protocol" "\n";
		goto failLabel;
	}

	if (!connection->connect())
	{
		goto failLabel;
	}

	while (working)
	{
		connection->receive(message);
		std::cout << "Message: " << message.getData() << '\n';
		if (message.getString() == "exit")
		{
			working = false;
		}
		else
		{
			connection->send(message);
		}
	}

exitLabel:
	return true;

failLabel:
	return false;
}

void Server::printUsage()
{
	using std::cout;
	cout << "Options:\n";
	cout << "\t" "-t   --proto   <TCP or UDP>" "\n"
			"\t" "-p   --port    <port number>" "\n";
	cout.flush();
}

bool Server::validAndParseArguments(int argc, char **argv)
{
	using std::cout;
	using std::strcmp;

	if (argc != 5)
	{
		goto failLabel;
	}
	else
	{
		const char *strProtocol = nullptr;
		const char *strPort = nullptr;
		for (int i = 1; i < argc; i += 2)
		{
			if (!strcmp("-t", argv[i]) || !strcmp("--proto", argv[i]))
			{
				strProtocol = argv[i+1];
			}
			else if (!strcmp("-p", argv[i]) || !strcmp("--port", argv[i]))
			{
				strPort = argv[i+1];
			}
			else goto failLabel;
		}
		connection = new ServerConnection(strProtocol, strPort);
	}
	return true;

failLabel:
	cout << argv[0] << " <options>" "\n";
	printUsage();
	return false;
}
