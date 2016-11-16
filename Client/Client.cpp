#include <iostream>
#include <string.h>
#include "Client.hpp"

Client::Client(int argc, char **argv) : printed(false), connection(nullptr)
{
	if (validAndParseArguments(argc, argv))
	{
		// base client setting
	}
	else
	{
		// make invalid
		printed = true;
	}
}

Client::~Client()
{
	delete connection;
}

bool Client::start()
{
	using std::cin;
	using std::cout;
	using std::cerr;

	// simple command line
	bool working = true;
	Message message;

	if (printed)
	{
		goto exitLabel;
	}

	if (connection->getProtocol() == Connection::Protocol::UNKNOWN)
	{
		cerr << "Client::start(): unknown protocol" "\n";
		goto failLabel;
	}

	if (!connection->connect())
	{
		goto failLabel;
	}

	while (working)
	{
		cout << "-> "; cin >> message.getString();
		connection->send(message);
		if (message.getString() == "exit")
		{
			working = false;
		}
		else
		{
			connection->receive(message);
			cout << "Recieved: " << message.getData() << '\n';
		}
	}

exitLabel:
	return true;

failLabel:
	return false;
}

// private
void Client::printUsage()
{
	using std::cout;
	cout << "Options:\n";
	cout << "\t" "-t   --proto <TCP/UDP>" "\n"
			"\t" "-p   --port <port number>" "\n"
			"\t" "-a   --address <server address>" "\n";
	cout.flush();
}

bool Client::validAndParseArguments(int argc, char **argv)
{
	using std::cout;
	if (argc != 7)
	{
		goto failLabel;
	}
	else
	{
		const char *strAddress = nullptr;
		const char *strProtocol = nullptr;
		const char *strPort = nullptr;
		for (int i = 1; i < argc; i += 2)
		{
			if (!strcmp("-t", argv[i]) || !strcmp("--proto", argv[i]))
			{
				strProtocol = argv[i + 1];
			}
			else if	(!strcmp("-p", argv[i]) || !strcmp("--port", argv[i]))
			{
				strPort = argv[i + 1];
			}
			else if (!strcmp("-a", argv[i]) || !strcmp("--address", argv[i]))
			{
				strAddress = argv[i + 1];
			}
			else goto failLabel;
		}
		connection = new ClientConnection(strAddress, strPort, strProtocol);
	}
	return true;

failLabel:
	cout << argv[0] << " <options>" "\n";
	printUsage();
	return false;
}
