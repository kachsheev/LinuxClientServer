#ifndef CLIENT_CLIENTCONNECTION_HPP
#define CLIENT_CLIENTCONNECTION_HPP

#include <netdb.h>
#include "../Common/Connection.hpp"

class ClientConnection: public Connection
{
public:
	ClientConnection();
	ClientConnection(const char *strAddress, const char *strPort,
			const char *strProtocol);

	virtual ~ClientConnection();

	virtual bool connect();

	virtual bool send(const Message &message);
	virtual bool receive(Message &message);

private:
	hostent *serverHost;
};

#endif // CLIENT_CLIENTCONNECTION_HPP
