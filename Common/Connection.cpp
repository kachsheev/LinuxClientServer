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
		sock(0),
		protocol(Protocol::UNKNOWN)
{
	using std::strcmp;
	using std::atoi;

	memset(&sockAddr, 0, sizeof(sockAddr));
	if (strPort != nullptr && strPort != nullptr)
	{
		if (strcmp("TCP", strProtocol))
		{
			protocol = Protocol::TCP;
		}
		else if (strcmp("TCP", strProtocol))
		{
			protocol = Protocol::UDP;
		}
		sock = socket(AF_INET, SOCK_STREAM, static_cast<int>(protocol));
		sockAddr.sin_port = static_cast<in_port_t>(atoi(strPort));
	}
}

Connection::~Connection()
{
	if (sock > 0)
	{
		close(sock);
	}
}
