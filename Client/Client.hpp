#ifndef CLIENT_CLIENT_HPP
#define CLIENT_CLIENT_HPP

#include <string>
#include "ClientConnection.hpp"

class Client: public AbstractApplication
{
public:
	Client(int argc, char **argv);
	virtual ~Client();

	virtual bool start();

private:
	// funcs
	void printUsage();
	bool validArguments(int argc, char **argv);

	void udpProcess(const std::string &message);
	void tcpProcess(const std::string &message);

	// data
	ClientConnection connection;

	// useless
	Client() = delete;
	Client(const Client &) = delete;
	Client(Client &&) = delete;

	Client &operator =(const Client &);
	Client &operator =(Client &&);
};

#endif // CLIENT_CLIENT_HPP