#pragma once
#include "Socket.h"
#include "CommandingEngine.h"
//#include "RTDB.h"
#include <thread>

class ClientHandler {
private:
	list<SocketStruct*> acceptedSocketList;
	static ClientHandler* instance;
	ClientHandler();
public:
	static ClientHandler* Instance();
	void ServerThread(char* port);
	void Receive(SocketStruct* socket);
	void AlarmListening();
	list<SocketStruct*> GetAcceptedSocketList();
	void SendDeleteAlarm(Alarm* a);
};

void ReceiveFunction(SocketStruct* socket);
void AlarmListeningThread(list<SocketStruct*>* acceptedSocketList);

