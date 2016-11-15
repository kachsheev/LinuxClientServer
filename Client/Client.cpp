#include <iostream>
#include "Client.hpp"

Client::Client(int argc, char **argv)
{
	if (validArguments(argc, argv))
	{
		// base client setting
	}
	else
	{
		// make invalid
	}
}

Client::~Client()
{
	// if valid - do something
}

bool Client::start()
{
	bool working = true;

	// simple command line


	while (working)
	{
		switch (con)
	}

	// if invalid
	return false;
}

// private
void Client::printUsage()
{
	using std::cout;
	cout << "Options:\n";
	cout << "\t" "-t   --proto <TCP/UDP>" "\n"
			"\t" "-p   --port <port number>" "\n"
			"\t" "-a   --address <server address>" "\n";
	cout.flush();
}

bool Client::validArguments(int argc, char **argv)
{
	using std::cout;
	if (argc != 7)
	{
		cout << argv[0] << " <options>" "\n";
		printUsage();
		return false;
	}
	return true;
}
