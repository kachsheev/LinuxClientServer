#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "Connection.hpp"

Connection::Connection() : Connection(nullptr, nullptr)
{
}

Connection::Connection(const char *strProtocol, const char *strPort):
		sock(0), port(0),
		protocol(Protocol::UNKNOWN)
{
	using std::strcmp;
	using std::atoi;
	using std::cerr;

	if (strPort != nullptr || strPort != nullptr)
	{
		int sockType = 0;
		if (!strcmp("TCP", strProtocol))
		{
			protocol = Protocol::TCP;
			sockType = SOCK_STREAM;
		}
		else if (!strcmp("UDP", strProtocol))
		{
			protocol = Protocol::UDP;
			sockType = SOCK_DGRAM;
		}

		port = atoi(strPort);

		sock = socket(AF_INET, sockType, static_cast<int>(protocol));
		if (sock < 0)
		{
			cerr << "Connection::Connection(): socket error" "\n";
		}

		memset(&sockAddr, 0, sizeof(sockAddr));
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons(port);
	}
}

Connection::~Connection()
{
	if (sock > 0)
	{
		close(sock);
	}
}
