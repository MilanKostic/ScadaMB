#include <iostream>
#include "Socket.h"
using namespace std;

int main() {

	SOCKET serverSocket = Socket::Instance()->Connect("127.0.0.1", 9000);

	int menuValue;
	do {
		cout << "1. Prikaz trenutnih velicina";
		cout << "2. Izmjena vrijednosti velicina";
		cout << "0. Izlaz";
		cin >> menuValue;

		switch (menuValue) {
		case 1: { ShowMonitoringValues(serverSocket); break; }
		case 2: { ServeCommandMenu(); break; }
		}

	} while (menuValue != 0);

	//Socket::Instance()->Send(serverSocket, null, null);
}

void ShowMonitoringValues(SOCKET serverSocket) {

	Socket::Instance()->Send(serverSocket, null, null);
}