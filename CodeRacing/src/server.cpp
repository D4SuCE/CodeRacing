#include <iostream>
#include "server.h"

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

void Server::createWorld()
{
	gw = gwm.createGameWorld("1");
	gw->raceCar.throttle = 0.5f;
	gwm.renderWorld("1");
}

void Server::sendData()
{
	char buffer[sizeof(float) * 7];

	gw->getNextFrame();
	gwm.renderWorld("1");

	std::vector<float> data;

	data.push_back(gw->raceCar.speed);
	data.push_back(gw->raceCar.rotation);
	data.push_back(gw->raceCar.radars[0].rayHitDistance);
	data.push_back(gw->raceCar.radars[1].rayHitDistance);
	data.push_back(gw->raceCar.radars[2].rayHitDistance);
	data.push_back(gw->raceCar.radars[3].rayHitDistance);
	data.push_back(gw->raceCar.radars[4].rayHitDistance);

	int counter = 0;

	for (float& detail : data)
	{
		memcpy(buffer + counter, &detail, sizeof(float));
		counter += 4;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(16));

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

		gw->raceCar.steerWheel = data[0];
		gw->raceCar.throttle = data[1];
		gw->raceCar.brake = data[2];
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
	createWorld();
	communication();
}