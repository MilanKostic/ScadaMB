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
}

void ShowMonitoringValues(SOCKET serverSocket, char* sendBuffer) {
	sendBuffer[0] = 'r';
	Socket::Instance()->Send(serverSocket, sendBuffer, 6);
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