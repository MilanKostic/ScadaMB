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

int main()
{
	//ClientHandler::Instance()->ServerThread("9000");
	/*SOCKET socket = Socket::Instance()->Connect("127.0.0.1", 502);

	
	ReadCoilsMessage* msg = new ReadCoilsMessage(1, 9);
	ReadCoilsMessage readCoilsMsg = *(ReadCoilsMessage*)ModbusDriverTCP().SendModbusMessage(socket, (ModbusMessageTCP*)msg);

	ReadDescreteInputsMessage* msgDescreteInputs = new ReadDescreteInputsMessage(10001, 6);
	ReadDescreteInputsMessage response = *(ReadDescreteInputsMessage*)ModbusDriverTCP().SendModbusMessage(socket, (ModbusMessageTCP*)msgDescreteInputs);
	
	
	ReadInputRegistersMessage* msgHolding = new ReadInputRegistersMessage(10001, 6);
	ReadInputRegistersMessage response = *(ReadInputRegistersMessage*)ModbusDriverTCP().SendModbusMessage(socket, (ModbusMessageTCP*)msgHolding);
	
	
	WriteSingleCoilMessage* testWrite = new WriteSingleCoilMessage(1, 0);
	WriteSingleCoilMessage retWrite = *(WriteSingleCoilMessage*)ModbusDriverTCP().SendModbusMessage(socket, (ModbusMessageTCP*)testWrite);

	WriteSingleRegisterMessage* testSingleReg = new WriteSingleRegisterMessage(40001, 25);
	WriteSingleCoilMessage response = *(WriteSingleCoilMessage*)ModbusDriverTCP().SendModbusMessage(socket, (ModbusMessageTCP*)testSingleReg);*/

	/*ReadHoldingRegistersMessage* readHolding = new ReadHoldingRegistersMessage(40001, 3);
	ReadHoldingRegistersMessage resp = *(ReadHoldingRegistersMessage*)ModbusDriverTCP().SendModbusMessage(socket, readHolding);
	*/

	//closesocket(socket);
	
	
	ScadaConfig sc;
	sc.LoadScadaParams();

	system("pause");
	return 0;
}