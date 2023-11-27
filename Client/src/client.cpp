#include <iostream>
#include <vector>
#include "client.h"
#include <chrono>
#include <thread>

float RandomFloat1(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

Client::Client()
	: ipaddr("127.0.0.1"), port(9999)
{
}

Client::Client(const std::string& ipaddr, int port)
	: ipaddr(ipaddr), port(port)
{
}

Client::~Client()
{
	WSACleanup();
	closesocket(clientSocket);
}

void Client::init()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		throw std::runtime_error("WSA not created! (Client)");
	}

	addr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	clientAddrLen = sizeof(addr);
}

void Client::createSocket()
{
	if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		throw std::runtime_error("Server socket not created! (Client)");
	}
}

void Client::connectSocket()
{
	if (connect(clientSocket, (SOCKADDR*)&addr, clientAddrLen) != 0)
	{
		throw std::runtime_error("Couldn't connect to server!");
	}
}

void Client::receiveData()
{
	char buffer[sizeof(float) * 7];

	int recvLength = recv(clientSocket, buffer, sizeof(buffer), 0);

	if (recvLength > 0)
	{
		int counter = 0;

		std::vector<float> data(7, 0);

		for (float& detail : data)
		{
			memcpy(&detail, buffer + counter, sizeof(float));
			counter += 4;
		}

		std::cout << "Client: \n";
		std::cout << "Speed: " << data[0] << std::endl;
		std::cout << "Ratation: " << data[1] << std::endl;
		std::cout << "Radar1: " << data[2] << std::endl;
		std::cout << "Radar2: " << data[3] << std::endl;
		std::cout << "Radar3: " << data[4] << std::endl;
		std::cout << "Radar4: " << data[5] << std::endl;
		std::cout << "Radar5: " << data[6] << std::endl;
	}
}

//void Client::sendData()
//{
//	char buffer[sizeof(float) * 3];
//
//	std::vector<float> data = car.getClientInfo();
//
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

void Client::sendData()
{
	char buffer[sizeof(float) * 3];

	std::vector<float> data;

	for (int i = 0; i < 3; ++i)
	{
		data.push_back(RandomFloat1(0.0, 1.0));
	}

	int counter = 0;

	for (float& detail : data)
	{
		memcpy(buffer + counter, &detail, sizeof(float));
		counter += 4;
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(500));

	send(clientSocket, buffer, sizeof(buffer), 0);
}

void Client::communication()
{
	while (true)
	{
		receiveData();
		sendData();
	}
}

void Client::start()
{
	init();
	createSocket();
	connectSocket();
	communication();
}
