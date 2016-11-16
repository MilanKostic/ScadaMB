#include "ClientHandler.h"
#include "RTDB.h"

void ReceiveFunction(SocketStruct* socket) {
	ClientHandler::Instance()->Receive(socket);
}

void AlarmListeningThread(list<SocketStruct*>* acceptedSocketList)
{
	while (true) {
		for each (pair<int, list<Alarm*>> rtuPair in RTDB::Instance()->GetAlarmMap())
		{
			for each (Alarm* alarm in rtuPair.second)
			{
				if (!alarm->IsInhibition() && !alarm->GetIsSend())
				{
					std::this_thread::sleep_for(chrono::microseconds(alarm->GetSleepTime()));
					for each (SocketStruct *soc in *acceptedSocketList)
					{
						int msgLen = alarm->GetAlarmMessage().length() + 6;
						char * writable = new char[msgLen];
						writable[0] = 'A';
						*(int*)&writable[1] = alarm->GetAlarmId();
						memcpy(&writable[5], alarm->GetAlarmMessage().c_str(), alarm->GetAlarmMessage().length());
						writable[msgLen - 1] = '\0';
						Socket::Instance()->Send(soc, writable, msgLen);
						delete[] writable;
						alarm->SetIsSend(true);
						//alarm->setSleepTime(5000);
					}
				}
			}
		}

	}
}



ClientHandler* ClientHandler::instance = NULL;

ClientHandler::ClientHandler() {

}

ClientHandler* ClientHandler::Instance()
{
	if (instance == NULL) {
		instance = new ClientHandler();
	}
	return instance;
}

void ClientHandler::ServerThread(char * port)
{
	SOCKET listenSocket = INVALID_SOCKET;
	int iResult;

	if (!Socket::Instance()->InitializeWindowsSockets())
	{
		return;
	}

	// Prepare address information structures
	addrinfo *resultingAddress = NULL;
	addrinfo hints;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;       // IPv4 address
	hints.ai_socktype = SOCK_STREAM; // Provide reliable data streaming
	hints.ai_protocol = IPPROTO_TCP; // Use TCP protocol
	hints.ai_flags = AI_PASSIVE;     // 

									 // Resolve the server address and port
	iResult = getaddrinfo(NULL, port, &hints, &resultingAddress);
	if (iResult != 0)
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return;
	}

	// Create a SOCKET for connecting to server
	listenSocket = socket(AF_INET,      // IPv4 address famly
		SOCK_STREAM,  // stream socket
		IPPROTO_TCP); // TCP

	if (listenSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(resultingAddress);
		WSACleanup();
		return;
	}

	// Setup the TCP listening socket - bind port number and local address 
	// to socket
	iResult = ::bind(listenSocket, resultingAddress->ai_addr, (int)resultingAddress->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(resultingAddress);
		closesocket(listenSocket);
		WSACleanup();
		return;
	}

	// Since we don't need resultingAddress any more, free it
	freeaddrinfo(resultingAddress);

	unsigned long int nonBlockingMode = 1;
	iResult = ioctlsocket(listenSocket, FIONBIO, &nonBlockingMode);
	if (iResult == SOCKET_ERROR)
	{
		printf("ioctlsocket failed with error: %ld\n", WSAGetLastError());
		return;
	}

	// Set listenSocket in listening mode
	iResult = listen(listenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return;
	}

	while (true) {

		int iResult = Socket::Instance()->Select(listenSocket, 0);
		if (iResult == SOCKET_ERROR)
		{
			fprintf(stderr, "select failed with error: %ld\n", WSAGetLastError());
			break;
		}

		if (iResult == 0)
		{
			Sleep(20);
			continue;
		}

		SOCKET acceptedSocket = accept(listenSocket, NULL, NULL);
		

		unsigned long int nonBlockingMode = 1;
		iResult = ioctlsocket(acceptedSocket, FIONBIO, &nonBlockingMode);

		if (iResult == SOCKET_ERROR)
		{
			printf("ioctlsocket failed with error: %ld\n", WSAGetLastError());
			continue;
		}

		if (acceptedSocket == INVALID_SOCKET)
		{
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			break;
		}

		SocketStruct sc;
		sc.socket = acceptedSocket;

		acceptedSocketList.push_back(&sc);

		std::thread(&ReceiveFunction, &sc).detach();
		// da li ovdje raditi smijestanje u listu tredova
	}
	closesocket(listenSocket);
}

void ClientHandler::Receive(SocketStruct* socket) {
	char accessBuffer[6];

	while (true)
	{
		int iResultSelect = Socket::Instance()->Select(socket->socket, 0);
		if (iResultSelect == SOCKET_ERROR)
		{
			fprintf(stderr, "select failed with error: %ld\n", WSAGetLastError());
			continue;
		}

		if (iResultSelect == 0)
		{
			Sleep(20);
			continue;
		}
		socket->lock.lock();
		int iResult = recv(socket->socket, accessBuffer, 6, 0);
		socket->lock.unlock();

		if (iResult == SOCKET_ERROR) {
			printf("Error in receive: %d", WSAGetLastError());
			break;
		}

		if (iResult == 0) {
			printf("Connection is closed\n");
			break; // Zatvorena konekcija
		}
		
		if (accessBuffer[0] == 'r')
		{
			char* retVal = RTDB::Instance()->GetCurrentValues();
			Socket::Instance()->Send(socket, retVal, strlen(retVal)+1);
		}
		else if (accessBuffer[0] == 'A')
		{
			RTDB::Instance()->ProcessAlarm(*(int*)&accessBuffer[1], accessBuffer[5]);
		}
		else
		{
			CommandingEngine::Instance()->CreateCommand(accessBuffer);
		}
	}
	acceptedSocketList.remove(socket);
	closesocket(socket->socket);
}

void ClientHandler::AlarmListening()
{
	std::thread(AlarmListeningThread, &acceptedSocketList).detach();
}

list<SocketStruct*> ClientHandler::GetAcceptedSocketList()
{
	return acceptedSocketList;
}

