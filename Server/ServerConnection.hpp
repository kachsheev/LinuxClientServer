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

	virtual bool send(const Message &message);
	virtual bool recieve(Message &message);
private:
	int clientSock;
	socklen_t clientAddrSize;
	sockaddr_in clientAddr;
};

#endif // SERVER_SERVERCONNECTION_HPP
