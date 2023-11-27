#pragma once

#include <string>
#include <WinSock2.h>
#include "GameWorldManager.h"

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996)

class Server
{
private:
	std::string ipaddr;
	int port;
	WSAData wsa;
	SOCKADDR_IN addr;
	int serverAddrLen;
	int serverSocket;
	int clientSocket;
	GameWorldManager gwm;
	GameWorld* gw;

public:
	Server();
	Server(const std::string& ipaddr, int port);
	~Server();

private:
	void init();
	void createSocket();
	void bindSocket();
	void listenSocket();
	void acceptSocket();
	void createWorld();
	void sendData();
	void receiveData();
	void communication();

public:
	void start();
};