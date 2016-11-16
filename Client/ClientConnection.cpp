#include <unistd.h>
#include <iostream>
#include <cstring>
#include "ClientConnection.hpp"

ClientConnection::ClientConnection() : ClientConnection(nullptr, nullptr, nullptr)
{
}

ClientConnection::ClientConnection(const char *strAddress,
		const char *strPort, const char *strProtocol) :
		Connection(strProtocol, strPort)
{
	using std::cerr;
	using std::memset;
	using std::strncpy;

	if (strAddress != nullptr)
	{
		serverHost = gethostbyname(strAddress);
		if (serverHost == nullptr)
		{
			cerr << "ClientConnection::ClientConnection(): host not found." "\n";
		}
		else
		{
			strncpy((char *)&getSockAddress().sin_addr.s_addr,
					(char *)serverHost->h_addr, serverHost->h_length);
		}
	}
}

ClientConnection::~ClientConnection()
{
}

bool ClientConnection::connect()
{
	using std::cerr;

	sockaddr_in &sockAddr = getSockAddress();
	int connectionResult = ::connect(getSocket(), reinterpret_cast<sockaddr *>(&sockAddr), sizeof(sockAddr));
	if (connectionResult < 0)
	{
		cerr << "ClientConnection::connect(): connection error (" << connectionResult << ")\n";
		return false;
	}
	return true;
}

bool ClientConnection::send(const Message &message)
{
	using std::cerr;

	ssize_t realWrite = 0;
	switch (getProtocol())
	{
		case Protocol::TCP:
		{
			realWrite = write(getSocket(), message.getData(), message.getDataSize());
			if (realWrite < 0)
			{
				cerr << "ClientConnection::recieve(): TCP send error" "\n";
				return false;
			}
			break;
		}
		case Protocol::UDP:
		{
			sockaddr_in &sockAddr = getSockAddress();
			realWrite = sendto(getSocket(),
					message.getData(), message.getDataSize(),
					0, reinterpret_cast<sockaddr *>(&sockAddr), sizeof(sockAddr));
			if (realWrite < 0)
			{
				cerr << "ClientConnection::recieve(): UDP send error" "\n";
				return false;
			}
			break;
		}
		default:
			break;
	}
	return true;
}

bool ClientConnection::receive(Message &message)
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
				realRead = read(getSocket(), buff, Message::MAX_BUFFER_SIZE);
			}
			if (realRead < 0)
			{
				cerr << "ServerConnection::recieve(): TCP recieve error" "\n";
				return false;
			}
				break;
		}
		case Protocol::UDP:
		{
			sockaddr_in &serverAddr = getSockAddress();
			socklen_t serverAddrSize = sizeof(serverAddr);
			while (realRead == 0)
			{
				realRead = recvfrom(getSocket(),
						buff, Message::MAX_BUFFER_SIZE,
						0, reinterpret_cast<sockaddr *>(&serverAddr), &serverAddrSize);
			}
			if (realRead < 0)
			{
				cerr << "ServerConnection::recieve(): UDP recieve error" "\n";
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
