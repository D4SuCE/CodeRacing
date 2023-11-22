#include <iostream>
#include "offline-client-server/server.h"

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

Server::Server()
	: ipaddr("127.0.0.1"), port(9999)
{
}

Server::Server(const std::string& ipaddr, int port)
	: ipaddr(ipaddr), port(port)
{
}

Server::~Server()
{
	WSACleanup();
	closesocket(serverSocket);
	closesocket(clientSocket);
}

void Server::init()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		throw std::runtime_error("WSA not created! (Server)");
	}

	addr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	serverAddrLen = sizeof(addr);
}

void Server::createSocket()
{
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		throw std::runtime_error("Server socket not created! (Server)");
	}
}

void Server::bindSocket()
{
	if (bind(serverSocket, (SOCKADDR*)&addr, serverAddrLen) != 0)
	{
		throw std::runtime_error("Couldn't bind socket!");
	}
}

void Server::listenSocket()
{
	if (listen(serverSocket, SOMAXCONN) != 0)
	{
		throw std::runtime_error("Couldn't listen socket!");
	}
}

void Server::acceptSocket()
{
	if ((clientSocket = accept(serverSocket, (SOCKADDR*)&addr, &serverAddrLen)) < 0)
	{
		std::cout << "Couldn't accept socket!" << std::endl;
	}
}

//void Server::sendData()
//{
//	char buffer[sizeof(float) * 7];
//
//	std::vector<float> data = car.getServerInfo();
//	int counter = 0;
//
//	for (float& detail : data)
//	{
//		memcpy(buffer + counter, &detail, sizeof(float));
//		counter += 4;
//	}
//
//	send(clientSocket, buffer, sizeof(buffer), 0);
//}

void Server::sendData()
{
	char buffer[sizeof(float) * 7];

	std::vector<float> data;

	for (int i = 0; i < 7; ++i)
	{
		data.push_back(RandomFloat(0.0, 1.0));
	}

	int counter = 0;

	for (float& detail : data)
	{
		memcpy(buffer + counter, &detail, sizeof(float));
		counter += 4;
	}

	send(clientSocket, buffer, sizeof(buffer), 0);
}

void Server::receiveData()
{
	char buffer[sizeof(float) * 3];

	int recvLength = recv(clientSocket, buffer, sizeof(buffer), 0);

	if (recvLength > 0)
	{
		int counter = 0;
		std::vector<float> data(3, 0);
		for (float& detail : data)
		{
			memcpy(&detail, buffer + counter, sizeof(float));
			counter += 4;
		}

		std::cout << "Server: \n";
		std::cout << "TurnWheel: " << data[0] << std::endl;
		std::cout << "Gaz: " << data[1] << std::endl;
		std::cout << "Brakes: " << data[2] << std::endl;
	}
}

void Server::communication()
{
	while (true)
	{
		sendData();
		receiveData();
	}
}

void Server::start()
{
	init();
	createSocket();
	bindSocket();
	listenSocket();
	acceptSocket();
	communication();
}