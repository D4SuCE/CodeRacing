#pragma once

#include <string>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996)

class Client
{
private:
	std::string ipaddr;
	int port;
	WSAData wsa;
	SOCKADDR_IN addr;
	int clientAddrLen;
	int clientSocket;

public:
	Client();
	Client(const std::string& ipaddr, int port);
	~Client();

private:
	void init();
	void createSocket();
	void connectSocket();
	void receiveData();
	void sendData();
	void communication();

public:
	void start();
};