#include "RTU.h"

RTU::RTU(int id, string industrialProtocol, string transportProtocol, string ipAddress, int port)
{
	RTU::id = id;
	RTU::industrialProtocol = industrialProtocol;
	RTU::transportProtocol = transportProtocol;
	RTU::ipAddress = ipAddress;
	RTU::port = port;
	char* ip = new char[this->ipAddress.size() + 1];
	memcpy(ip, this->ipAddress.c_str(), this->ipAddress.size());
	ip[this->ipAddress.size()] = '\0';
	socket.socket = Socket::Instance()->Connect(ip, this->port);
}

map<unsigned short, AnalogInput*> RTU::GetAnalogInputList() {
	return analogInputList;
}

map<unsigned short, AnalogOutput*> RTU::GetAnalogOutoputList()
{
	return analogOutputList;
}

map<unsigned short, DigitalDevice*> RTU::GetDigitalDevices()
{
	return digitalDevices;
}

void RTU::AddAnalogInput(AnalogInput * analogInput)
{
	this->analogInputList.insert(std::pair<unsigned short, AnalogInput*>(analogInput->GetAddress(), analogInput));
}

void RTU::AddAnalogOutput(AnalogOutput * analogOutput)
{
	this->analogOutputList.insert(std::pair<unsigned short, AnalogOutput*>(analogOutput->GetAddress(), analogOutput));
}

void RTU::AddDigitalDevice(DigitalDevice * digitalDevice)
{
	this->digitalDevices.insert(std::pair<unsigned short, DigitalDevice*>(digitalDevice->GetId(), digitalDevice));
}

double RTU::GetAnalogOutputValue(unsigned short address)
{
	for each(std::pair<unsigned short, AnalogOutput*> ao in this->analogOutputList)
	{
		if (ao.second->GetAddress() == address) return ao.second->GetRaw();
	}
	return 0.0;
}

SocketStruct* RTU::GetSocket()
{
	return &socket;
}

void RTU::SetIndustrialProtocol(string protocol)
{
	RTU::industrialProtocol = protocol;
}

void RTU::SetTransportProtocol(string protocol)
{
	RTU::transportProtocol = transportProtocol;
}

int RTU::GetID()
{
	return id;
}

string RTU::GetIndustrialProtocol()
{
	return industrialProtocol;
}

string RTU::GetTrasportProtocol()
{
	return transportProtocol;
}

string RTU::GetIpAddress()
{
	return ipAddress;
}

int RTU::GetPort()
{
	return port;
}
