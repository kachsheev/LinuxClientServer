#ifndef COMMON_CONNECTION_HPP
#define COMMON_CONNECTION_HPP

#include <netinet/in.h>
#include "Message.hpp"

class Connection
{
public:
	enum class Protocol: int
	{
		UNKNOWN = IPPROTO_IP,
		TCP = IPPROTO_TCP,
		UDP = IPPROTO_UDP
	};

	Connection();
	Connection(const char *strProtocol, const char *strPort);
	virtual ~Connection();

	Protocol getProtocol()
	{
		return protocol;
	}

	int getPort()
	{
		return port;
	}

	int getSocket()
	{
		return sock;
	}

	sockaddr_in &getSockAddress()
	{
		return sockAddr;
	}

	virtual bool connect() = 0;

	virtual bool send(const Message &message) = 0;
	virtual bool receive(Message &message) = 0;

private:
	int sock;
	int port;
	sockaddr_in sockAddr;
	Protocol protocol;
};

#endif // COMMON_CONNECTION_HPP
