#pragma once
#include "Socket.h"
#include "CommandingEngine.h"
//#include "RTDB.h"
#include <thread>

class ClientHandler {
private:
	static ClientHandler* instance;
	ClientHandler();
public:
	static ClientHandler* Instance();
	void ServerThread(char* port);
	void Receive(SocketStruct* socket);
};

void ReceiveFunction(SocketStruct* socket);

