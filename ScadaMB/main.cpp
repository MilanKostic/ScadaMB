#include <iostream>
#include "Socket.h"
#include "ReadCoilsMessage.h"
#include "ModbusDriverTCP.h"
#include "ReadHoldingRegistersMessage.h"
#include "ReadInputRegistersMessage.h"
#include "WriteSingleCoilMessage.h"
#include "WriteSingleRegisterMessage.h"
#include "ReadHoldingRegistersMessage.h"
#include "ClientHandler.h"
#include "ScadaConfig.h"
#include "ReadDescreteInputsMessage.h"
#include "PollEngine.h"

int main()
{

	ScadaConfig sc;
	sc.LoadScadaParams();

	
	CommandingEngine::Instance()->StartIncrement100UnitPS();

	PollEngine pe;
	DataProcessingEngine* dpe = pe.GetDPE();

	thread(&PollThread, &pe).detach();
	thread(&ProcessThread, dpe).detach();
	
	ClientHandler::Instance()->AlarmListening();

	ClientHandler::Instance()->ServerThread("9000");
		
	system("pause");
	return 0;
}