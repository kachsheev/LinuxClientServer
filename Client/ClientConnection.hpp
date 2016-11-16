#ifndef CLIENT_CLIENTCONNECTION_HPP
#define CLIENT_CLIENTCONNECTION_HPP

#include <arpa/inet.h>
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
};

#endif // CLIENT_CLIENTCONNECTION_HPP
