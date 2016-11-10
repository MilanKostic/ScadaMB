#include <iostream>
#include "Socket.h"

using namespace std;

void ShowMonitoringValues(SOCKET serverSocket, char* sendBuffer);
void ServeCommandMenu(SOCKET serverSocket, char* sendBuffer);

int main() {

	SOCKET serverSocket = Socket::Instance()->Connect("127.0.0.1", 9000);
	char *sendBuffer = (char*)malloc(6);

	int menuValue;
	do {
		cout << "1. Prikaz trenutnih velicina\n";
		cout << "2. Izmjena vrijednosti velicina\n";
		cout << "0. Izlaz\n";
		cin >> menuValue;

		switch (menuValue) {
		case 1: { ShowMonitoringValues(serverSocket, sendBuffer); break; }
		case 2: { ServeCommandMenu(serverSocket, sendBuffer); break; }
		}

	} while (menuValue != 0);
	free(sendBuffer);
}

void ShowMonitoringValues(SOCKET serverSocket, char* sendBuffer) {
	sendBuffer[0] = 'r';
	
	char* accessBuffer = new char(1024);
	Socket::Instance()->Send(serverSocket, sendBuffer, 6);
	while (true)
	{
		int iResultSelect = Socket::Instance()->Select(serverSocket, 0);
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
		
		int iResult = recv(serverSocket, accessBuffer, 1024, 0);
		
		if (iResult == SOCKET_ERROR) {
			printf("Error in receive: %d", WSAGetLastError());
			break;
		}
		if (iResult == 0) {
			printf("Connection is closed\n");
			break; // Zatvorena konekcija
		}

		if (iResult < 1024) {
			char *writeBuffer = new char(iResult);
			memcpy(writeBuffer, accessBuffer, iResult);
			cout << writeBuffer;
		}
		else {
			cout << accessBuffer;
		}
		
	}
	
}

void  ServeCommandMenu(SOCKET serverSocket, char* sendBuffer) {
	sendBuffer[0] = 'c';
	char menuValue;
	int value;
	do {
		cout << "1. Kolicina vode\n";
		cout << "2. Kolicina pijeska\n";
		cout << "3. Kolicina sljunka\n";
		cout << "4. Mjesalica puna/nije puna (1/0)\n";
		cout << "5. Kamion prisutan/nije prisutan (1/0)\n";
		cout << "6. Mjesalica se prazni/ne prazni se (1/0)\n";
		cout << "0. Izlaz\n";
		cin >> menuValue;

		if (menuValue != '0') {
			cout << "Vrednost: ";
			cin >> value;
			sendBuffer[1] = menuValue;
			*(int*)&sendBuffer[2] = value;
			Socket::Instance()->Send(serverSocket, sendBuffer, 6);
		}
	} while (menuValue != '0');
}