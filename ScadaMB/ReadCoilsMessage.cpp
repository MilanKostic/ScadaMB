#include "ReadCoilsMessage.h"
#include <string>
#include "Socket.h"

ReadCoilsMessage::ReadCoilsMessage(unsigned short startingAddress, unsigned short numberOfCoils)
{
	this->functionCode = ModbusMessageTypes::READ_COILS;
	this->header.transactionIdentifier = htons(0x0001);
	this->header.protocolIdentifier = htons(0x0000);
	this->header.length = htons(6);
	this->header.unitIdentifier = 0x01;
	this->startingAddress = startingAddress;
	this->quantityOfCoils = numberOfCoils;
	this->messageLength = this->headerLength + 5;
}

ReadCoilsMessage::ReadCoilsMessage()
{
	this->functionCode = ModbusMessageTypes::READ_COILS;
}

ReadCoilsMessage::ReadCoilsMessage(char* bytes) : ModbusMessageTCP(bytes)
{
	this->functionCode = ModbusMessageTypes::READ_COILS;
	this->Deserialize(bytes);
}

char* ReadCoilsMessage::Serialize()
{
	char* retValue = new char[messageLength];

	*(Header*)&retValue[0] = header;
	retValue[headerLength] = functionCode;
	*(unsigned short*)&retValue[headerLength + 1] = htons(startingAddress);
	*(unsigned short*)&retValue[headerLength + 3] = htons(quantityOfCoils);

	return retValue;
}

void ReadCoilsMessage::Deserialize(char* msg)
{
	ModbusMessageTCP::Deserialize(msg);
	this->functionCode = msg[headerLength];
	char temp[2];
	temp[0] = msg[headerLength + 1];
	temp[1] = 0;
	memcpy(&this->byteCount, temp, 2);
	this->coilStatus = new char[this->byteCount];
	memcpy(this->coilStatus, &msg[headerLength + 2], this->byteCount);
	this->messageLength = headerLength + this->header.length - 1;
}

void ReadCoilsMessage::SetStartingAddress(unsigned short sa)
{
	this->startingAddress = sa;
}

void ReadCoilsMessage::setQuantityOfCoils(unsigned short qc)
{
	this->quantityOfCoils = qc;
}

unsigned short ReadCoilsMessage::GetQuantityOfCoils()
{
	return this->quantityOfCoils;
}

bool ReadCoilsMessage::GetBit(char c, unsigned short position)
{
	return (c >> position) & 0x01;
}

unsigned short ReadCoilsMessage::GetStartingAddress()
{
	return this->startingAddress;
}

void ReadCoilsMessage::Crunch(int rtuId, ModbusMessageTCP* req)
{
	ReadCoilsMessage* reqCoils = (ReadCoilsMessage*)req;
	RTU* rtu = RTDB::Instance()->GetRTU(rtuId);
	for each(std::pair<unsigned short, DigitalDevice*> device in rtu->GetDigitalDevices())
	{
		if (device.second->GetInAddresses()[0] == reqCoils->GetStartingAddress())
		{
			//unsigned short coilCount = reqCoils->GetQuantityOfCoils();
			bool coil1 = this->GetBit(this->coilStatus[0], 1);
			bool coil2 = this->GetBit(this->coilStatus[0], 2);
			if (coil1 && coil2) device.second->SetState(PointState::Error);
			else if (coil1 && !coil2) device.second->SetState(PointState::On);
			else if (!coil1 && coil2) device.second->SetState(PointState::Off);
			else if (!coil1 && !coil2) device.second->SetState(PointState::Progress);

			if (device.second->GetId() == PointAddress::dozvolaPraznjenjaMjesalice && device.second->GetPointState() == PointState::On && device.second->GetCommand() == PointState::Off)
			{
				//Generisi alarm
				RTU *rtu = RTDB::Instance()->GetRemotes().find(PointAddress::rtuId)->second;
				DigitalDevice *dev = rtu->GetDigitalDevices().find(PointAddress::dozvolaPraznjenjaMjesalice)->second;
				RTDB::Instance()->AddAlarm(new Alarm(rtu, dev, -1));
			}
			else if(device.second->GetPointState() == device.second->GetCommand() && device.second->GetId() == PointAddress::dozvolaPraznjenjaMjesalice)
			{
				RTDB::Instance()->RemoveAlarm(device.second);
			}
			break;
		}
	}
	

}

