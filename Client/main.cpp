#include <iostream>
#include "Socket.h"
#include "PointStates.h"

using namespace std;

typedef struct
{
	SocketStruct* socket;
	bool inputAlarm;
	char alarmBuffer[6];
	int alarmColor;
	char* alarmText;
}ThreadParams;

void ShowMonitoringValues(SocketStruct* serverSocket, char* sendBuffer);
void ServeCommandMenu(SocketStruct* serverSocket, char* sendBuffer);
void ListenForAlarms(ThreadParams* serverSocket);

int main() {

	SocketStruct serverSocket;
	serverSocket.socket = Socket::Instance()->Connect("127.0.0.1", 9000);

	ThreadParams param;
	param.socket = &serverSocket;
	param.inputAlarm = false;
	param.alarmText = NULL;
	param.alarmColor = 7;

	std::thread(ListenForAlarms, &param).detach();

	char *sendBuffer = (char*)malloc(6);
	char menuValue;
	do {
		cout << endl;

		if (param.alarmText != NULL && param.inputAlarm == false)
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, param.alarmColor);
			cout << param.alarmText << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}

		cout << "1. Prikaz trenutnih velicina\n";
		cout << "2. Izmjena vrijednosti velicina\n";
		cout << "0. Izlaz\n";
		
		cin >> menuValue;

		if (param.inputAlarm)
		{
			param.alarmBuffer[5] = menuValue;
			Socket::Instance()->Send(param.socket, param.alarmBuffer, 6);
			param.inputAlarm = false;
			system("cls");
			continue;
		}
		
		system("cls");

		switch (menuValue) 
		{
			case '1': { ShowMonitoringValues(&serverSocket, sendBuffer); break; }
			case '2': { ServeCommandMenu(&serverSocket, sendBuffer); break; }
		}
		
	} while (menuValue != '0');
	free(sendBuffer);
}

void ShowMonitoringValues(SocketStruct* serverSocket, char* sendBuffer) {
	sendBuffer[0] = 'r';
	
	Socket::Instance()->Send(serverSocket, sendBuffer, 6);
		
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
			if (value == 1)
			{
				*(int*)&sendBuffer[2] = PointState::On;
			}
			else
			{
				*(int*)&sendBuffer[2] = PointState::Off;
			}
			//*(int*)&sendBuffer[2] = value;
			Socket::Instance()->Send(serverSocket, sendBuffer, 6);
		}
	} while (menuValue != '0');
}

void ListenForAlarms(ThreadParams* params) {
	char* accessBuffer = new char[1024];
	while (true)
	{
		int iResultSelect = Socket::Instance()->Select(params->socket->socket, 0);
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

		params->socket->lock.lock();
		int iResult = recv(params->socket->socket, accessBuffer, 1024, 0);
		params->socket->lock.unlock();

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
		int coutInc = 0;
		if (accessBuffer[0] == 'A')
		{
			coutInc = 5;
			k = 12;
		}
		SetConsoleTextAttribute(hConsole, k);
		
		if (accessBuffer[0] == 'D')
		{
			delete[] params->alarmText;
			params->alarmText = NULL;
			continue;
		}
		cout << &accessBuffer[coutInc];

		if (accessBuffer[0] == 'A')
		{
			params->alarmBuffer[0] = 'A';
			memcpy(&params->alarmBuffer[1], &accessBuffer[1], 4);
			SetConsoleTextAttribute(hConsole, 7);
			params->inputAlarm = true;

			char* alarmPotvrdjen = "[Alarm je potvrdjen]\n\0";
			int alarmTextLen = strlen(&accessBuffer[coutInc]) + strlen(alarmPotvrdjen) + 1;
			params->alarmText = new char[alarmTextLen];
			memcpy(params->alarmText, &accessBuffer[coutInc], strlen(&accessBuffer[coutInc]));
			memcpy(&params->alarmText[strlen(&accessBuffer[coutInc])], alarmPotvrdjen, strlen(alarmPotvrdjen));
			params->alarmText[alarmTextLen - 1] = '\0';
			params->alarmColor = 10;
			
			cout << "Potvrdi alarm(Unesite p):";		
		}
		SetConsoleTextAttribute(hConsole, 7);

	}
}