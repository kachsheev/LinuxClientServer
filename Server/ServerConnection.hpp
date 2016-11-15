#ifndef SERVER_SERVERCONNECTION_HPP
#define SERVER_SERVERCONNECTION_HPP

#include "../Common/Connection.hpp"

class ServerConnection: public Connection
{
public:
	ServerConnection();
	ServerConnection(const char *strProtocol, const char *strPort);

	virtual ~ServerConnection();

	virtual bool connect();

private:
	int newSock;
	int clientLength;
	sockaddr_in clientAddress;
};

#endif // SERVER_SERVERCONNECTION_HPP
