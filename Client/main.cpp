#include "Client.hpp"

int main(int argc, char **argv)
{
	Client client(argc, argv);
	if (client.start())
	{
		return 0;
	}
	return 1;
}
