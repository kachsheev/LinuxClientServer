#include <unistd.h>
#include "ServerConnection.hpp"

ServerConnection::ServerConnection()
{
}

ServerConnection::ServerConnection(const char *strProtocol, const char *strPort):
		Connection(strProtocol, strPort)
{
}

ServerConnection::~ServerConnection()
{
	if (newSock > 0)
	{
		close(newSock);
	}
}

bool ServerConnection::connect()
{
	return false;
}
