#ifndef CLIENT_CLIENTCONNECTION_HPP
#define CLIENT_CLIENTCONNECTION_HPP

#include "../Common/Connection.hpp"

class ClientConnection: public Connection
{
public:
	ClientConnection();
	ClientConnection(const char *address, const char *strPort,
			const char *strProtocol);

	virtual ~ClientConnection();

private:

};

#endif // CLIENT_CLIENTCONNECTION_HPP
