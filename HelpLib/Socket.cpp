#include "Socket.h"

Socket* Socket::instance = NULL;

Socket::Socket()
{
	InitializeWindowsSockets();
}

Socket::~Socket() 
{ 
	delete instance;
}

bool Socket::InitializeWindowsSockets()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup failed with error: %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

Socket* Socket::Instance()
{
	if (instance == NULL)
	{
		instance = new Socket();
	}
	return instance;
}

int Socket::Select(SOCKET socket, int send)
{
	FD_SET set;
	timeval timeVal;

	FD_ZERO(&set);
	FD_SET(socket, &set);

	timeVal.tv_sec = 0;
	timeVal.tv_usec = 0;

	if (send)
	{
		return select(0, NULL, &set, NULL, &timeVal);
	}
	else
	{
		return select(0, &set, NULL, NULL, &timeVal);
	}
}

SOCKET Socket::Connect(char* ipAddress, int port)
{
	SOCKET connectSocket = INVALID_SOCKET;
	int iResult = 0;

	if (!InitializeWindowsSockets())
	{
		return connectSocket;
	}
	connectSocket = socket(AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP);

	if (connectSocket == INVALID_SOCKET)
	{
		std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return connectSocket;
	}

	// create and initialize address structure
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	//serverAddress.sin_addr.s_addr = inet_addr(ipAddress);
	inet_pton(AF_INET, ipAddress, &serverAddress.sin_addr);
	serverAddress.sin_port = htons(port);
	// connect to server specified in serverAddress and socket connectSocket
	if (connect(connectSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		printf("Unable to connect.\n");
		closesocket(connectSocket);
		WSACleanup();
		return INVALID_SOCKET;
	}

	unsigned long int nonBlockingMode = 1;
	iResult = ioctlsocket(connectSocket, FIONBIO, &nonBlockingMode);

	if (iResult == SOCKET_ERROR)
	{
		printf("ioctlsocket failed with error: %ld\n", WSAGetLastError());
		return INVALID_SOCKET;
	}

	return connectSocket;
}

bool Socket::Send(SocketStruct* socket, char* data, int length)
{
	socket->lock.lock();
	while (true)
	{

		int iResult = Select(socket->socket, 1);

		if (iResult == SOCKET_ERROR)
		{
			fprintf(stderr, "select failed with error: %ld\n", WSAGetLastError());
			socket->lock.unlock();
			return false;
		}

		if (iResult == 0)
		{
			this_thread::sleep_for(chrono::milliseconds(100));
			continue;
		}
		iResult = send(socket->socket, data, length, 0);

		if (iResult == SOCKET_ERROR)
		{
			printf("Socket error in send method\n");
			socket->lock.unlock();
			return false;
		}

		length -= iResult;
		data += iResult;
		if (length == 0)
		{
			socket->lock.unlock();
			return true;
		}
	}
	socket->lock.unlock();
}

