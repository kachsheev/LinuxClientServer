#include <unistd.h>
#include <cstring>
#include <iostream>
#include "ServerConnection.hpp"

ServerConnection::ServerConnection()
{
	memset(&clientAddr, 0, sizeof(clientAddr));
}

ServerConnection::ServerConnection(const char *strProtocol, const char *strPort):
		Connection(strProtocol, strPort)
{
	memset(&clientAddr, 0, sizeof(clientAddr));
	getSockAddress().sin_addr.s_addr = htonl(INADDR_ANY);
}

ServerConnection::~ServerConnection()
{
	using std::cout;

	if (clientSock > 0)
	{
		cout << "ServerConnection destroyed" "\n";
		close(clientSock);
	}
}

bool ServerConnection::connect()
{
	using std::cerr;

	sockaddr_in &sockAddr = getSockAddress();
	int bindResult = bind(getSocket(),
			reinterpret_cast<const sockaddr *>(&sockAddr),
			sizeof(sockAddr));
	if (bindResult < 0)
	{
		cerr << "ServerConnection::connect(): bind error (" << bindResult << ")\n";
		return false;
	}

	if (getProtocol() == Protocol::TCP)
	{
		listen(getSocket(), 1);

		clientAddrSize = sizeof(clientAddr);
		clientSock = accept(getSocket(),
				reinterpret_cast<sockaddr *>(&clientAddr),
				&clientAddrSize);
		if (clientSock < 0)
		{
			cerr << "ServerConnection::connect(): TCP accept error" "\n";
			return false;
		}
	}

	return true;
}

bool ServerConnection::send(const Message &message)
{
	using std::cerr;

	ssize_t realWrite = 0;
	switch (getProtocol())
	{
		case Protocol::TCP:
		{
			realWrite = write(clientSock, message.getData(), message.getDataSize());
			if (realWrite < 0)
			{
				cerr << "ServerConnection::recieve(): TCP send error" "\n";
				return false;
			}
			break;
		}
		case Protocol::UDP:
		{
			while (realWrite == 0)
			{
				realWrite = sendto(getSocket(), message.getData(), message.getDataSize(),
						0, reinterpret_cast<const sockaddr *>(&clientAddr), clientAddrSize);
			}
			if (realWrite < 0)
			{
				cerr << "ServerConnection::recieve(): UDP send error" "\n";
				return false;
			}
			break;
		}
		default:
			break;
	}
	return true;
}

bool ServerConnection::receive(Message &message)
{
	using std::cerr;

	char buff[Message::MAX_BUFFER_SIZE];
	ssize_t realRead = 0;
	switch (getProtocol())
	{
		case Protocol::TCP:
		{
			while (realRead == 0)
			{
				realRead = read(clientSock, buff, Message::MAX_BUFFER_SIZE);
			}
			if (realRead < 0)
			{
				cerr << "ServerConnection::receive(): TCP receive error" "\n";
				return false;
			}
			break;
		}
		case Protocol::UDP:
		{
			while (realRead <= 0)
			{
				realRead = recvfrom(getSocket(),
						buff, Message::MAX_BUFFER_SIZE,
						0, reinterpret_cast<sockaddr *>(&clientAddr), &clientAddrSize);
			}
			if (realRead < 0)
			{
				cerr << "ServerConnection::receive(): UDP receive error" "\n";
				return false;
			}
			break;
		}
		default:
			break;
	}

	message.clear();
	for (ssize_t i = 0; i < realRead; ++i)
	{
		message.getString().push_back(buff[i]);
	}
	return true;
}
