#include "Socket.h"

Socket* Socket::instance = NULL;

Socket::Socket()
{
	InitializeWindowsSockets();
}

Socket::~Socket() { }

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
		cout << "socket failed with error: " << WSAGetLastError() << endl;
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

bool Socket::Send(SOCKET socket, char* data, int length)
{
	while (true)
	{

		int iResult = Select(socket, 1);

		if (iResult == SOCKET_ERROR)
		{
			fprintf(stderr, "select failed with error: %ld\n", WSAGetLastError());
			return false;
		}

		if (iResult == 0)
		{
			Sleep(sendSleepInterval);
			continue;
		}
		iResult = send(socket, data, length, 0);

		if (iResult == SOCKET_ERROR)
		{
			printf("Socket error in send method\n");
			return false;
		}

		length -= iResult;
		data += iResult;
		if (length == 0)
		{
			return true;
		}
	}
}
