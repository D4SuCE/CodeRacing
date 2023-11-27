#include "client.h"
#include <iostream>

int main()
{
	try
	{
		Client client;
		client.start();
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}