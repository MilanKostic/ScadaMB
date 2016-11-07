#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

class Socket
{
private:
	const int sendSleepInterval = 20;
	static Socket* instance;
	Socket();
	~Socket();
	bool InitializeWindowsSockets();
public:
	static Socket* Instance();
	int Select(SOCKET socket, int send);
	SOCKET Connect(char* ipAddress, int port);
	bool Send(SOCKET socket, char* data, int length);
};
