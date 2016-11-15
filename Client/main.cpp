#include <iostream>
#include "Socket.h"

using namespace std;

void ShowMonitoringValues(SocketStruct* serverSocket, char* sendBuffer);
void ServeCommandMenu(SocketStruct* serverSocket, char* sendBuffer);
void ListenForAlarms(SocketStruct* serverSocket);

int main() {

	SocketStruct serverSocket;
	serverSocket.socket = Socket::Instance()->Connect("127.0.0.1", 9000);

	std::thread(ListenForAlarms, &serverSocket).detach();

	char *sendBuffer = (char*)malloc(6);
	int menuValue;
	do {
		cout << endl;
		cout << "1. Prikaz trenutnih velicina\n";
		cout << "2. Izmjena vrijednosti velicina\n";
		cout << "0. Izlaz\n";
		cin >> menuValue;

		system("cls");

		switch (menuValue) {
		case 1: { ShowMonitoringValues(&serverSocket, sendBuffer); break; }
		case 2: { ServeCommandMenu(&serverSocket, sendBuffer); break; }
		}
		
	} while (menuValue != 0);
	free(sendBuffer);
}

void ShowMonitoringValues(SocketStruct* serverSocket, char* sendBuffer) {
	sendBuffer[0] = 'r';
	
	//char* accessBuffer = new char[1024];

	Socket::Instance()->Send(serverSocket, sendBuffer, 6);
	/*while (true)
	{
		int iResultSelect = Socket::Instance()->Select(serverSocket->socket, 0);
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
		
		int iResult = recv(serverSocket->socket, accessBuffer, 1024, 0);
		
		if (iResult == SOCKET_ERROR) {
			printf("Error in receive: %d", WSAGetLastError());
			break;
		}
		if (iResult == 0) {
			printf("Connection is closed\n");
			break; // Zatvorena konekcija
		}

		if (iResult < 1024) {
			char *writeBuffer = new char[iResult];
			memcpy(writeBuffer, accessBuffer, iResult);
			cout << writeBuffer;
			break;
		}
		else {
			cout << accessBuffer;
		}
		
	}*/
	
}

void  ServeCommandMenu(SocketStruct* serverSocket, char* sendBuffer) {
	sendBuffer[0] = 'c';
	char menuValue;
	int value;
	do {
		cout << "1. Dozvola praznjenja mjesalice (1/0)\n";
		cout << "0. Izlaz\n";
		cin >> menuValue;
		
		system("cls");

		if (menuValue != '0') {
			cout << "Vrednost: ";
			cin >> value;
			sendBuffer[1] = menuValue;
			*(int*)&sendBuffer[2] = value;
			Socket::Instance()->Send(serverSocket, sendBuffer, 6);
		}
	} while (menuValue != '0');
}

void ListenForAlarms(SocketStruct* serverSocket) {
	char* accessBuffer = new char[1024];
	while (true)
	{
		int iResultSelect = Socket::Instance()->Select(serverSocket->socket, 0);
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

		int iResult = recv(serverSocket->socket, accessBuffer, 1024, 0);

		if (iResult == SOCKET_ERROR) {
			printf("Error in receive: %d", WSAGetLastError());
			break;
		}
		if (iResult == 0) {
			printf("Connection is closed\n");
			break; // Zatvorena konekcija
		}
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int k = 7;
		if (accessBuffer[0] == 'M') k = 12;
		SetConsoleTextAttribute(hConsole, k);

		if (iResult < 1024) {
			char *writeBuffer = new char[iResult];
			memcpy(writeBuffer, accessBuffer, iResult);
			cout << writeBuffer;
		}
		else {
			cout << accessBuffer;
		}

	}
}