#include "Server.hpp"

int main(int argc, char **argv)
{
	Server server(argc, argv);
	if (server.start())
	{
		return 0;
	}
	return 1;
}
