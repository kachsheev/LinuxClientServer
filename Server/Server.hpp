#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Common/AbstractApplication.hpp"
#include "ServerConnection.hpp"

class Server: public AbstractApplication
{
public:
	Server(int argc, char **argv);
	virtual ~Server();

	virtual bool start();

protected:
	void udpProcess();
	void tcpProcess();

private:
	// funcs
	void printUsage();
	bool validAndParseArguments(int argc, char **argv);
	void handleMessage(const Message &message);

	// data
	bool printed;
	ServerConnection *connection;

	// useless
	Server() = delete;
	Server(const Server &) = delete;
	Server(Server &&) = delete;

	Server &operator =(const Server &);
	Server &operator =(Server &&);
};

#endif // SERVER_HPP
