#include <cstring>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <iostream>
#include "Server.hpp"

Server::Server(int argc, char **argv) : printed(false), connection(nullptr)
{
	if (!validAndParseArguments(argc, argv))
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
			handleMessage(message);
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
				strProtocol = argv[i + 1];
			}
			else if (!strcmp("-p", argv[i]) || !strcmp("--port", argv[i]))
			{
				strPort = argv[i + 1];
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

void Server::handleMessage(const Message &message)
{
	using std::cout;
	using std::string;
	using std::vector;
	using std::sort;
	using std::for_each;

	uint8_t min = 9;
	uint8_t max = 0;
	uint32_t sum = 0;
	vector<uint8_t> numbers(32);
	numbers.clear();

	const string &stringMessage = message.getString();

	for (auto it = stringMessage.begin(); it != stringMessage.end(); ++it)
	{
		if (*it >= '0' && *it <= '9')
		{
			numbers.push_back(static_cast<uint8_t>(*it - '0'));
			sum += numbers.back();

			if (numbers.back() > max)
			{
				max = numbers.back();
			}

			if (numbers.back() < min)
			{
				min = numbers.back();
			}
		}
	}

	if (numbers.size())
	{
		sort(numbers.begin(), numbers.end(),
				[](uint8_t first, uint8_t last) -> bool {
					return (first > last);
		});

		cout << "Numbers:";
		for_each(numbers.begin(), numbers.end(),
				[](uint8_t number) {
					cout << ' ' << uint16_t(number);
		});
		cout << '\n';
		cout << "Min: " << uint16_t(min) << '\n'
				<< "Max: " << uint16_t(max) << '\n';
		cout.flush();
	}
}
