#pragma once
#include "Socket.h"
#include <thread>

class ClientHandler {
private:
	static ClientHandler* instance;
	ClientHandler();
public:
	static ClientHandler* Instance();
	void ServerThread(char* port);
	void Receive(SOCKET socket);
};

void ReceiveFunction(SOCKET socket);

