#ifndef COMMON_CONNECTION_HPP
#define COMMON_CONNECTION_HPP

#include <netinet/in.h>

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
		return sockAddr.sin_port;
	}

	int getSocket()
	{
		return sock;
	}

	virtual bool connect() = 0;

private:
	int sock;
	sockaddr_in sockAddr;
	Protocol protocol;
};

#endif // COMMON_CONNECTION_HPP
