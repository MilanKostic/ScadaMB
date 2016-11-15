#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Socket.h"

//#include "AnalogInput.h"
#include "AnalogOutput.h"
#include "DigitalDevice.h"
#include <map>

using namespace std;

class RTU {
private:
	int id;
	string industrialProtocol;
	string transportProtocol;
	string ipAddress;
	int port;
	SocketStruct socket;

	map<unsigned short, AnalogInput*> analogInputList;
	map<unsigned short, AnalogOutput*> analogOutputList;
	map<unsigned short, DigitalDevice*> digitalDevices;

public:
	RTU(int id, string industrialProtocol, string transportProtocol, string ipAddress, int port);
	
	void SetIndustrialProtocol(string protocol);
	void SetTransportProtocol(string protocol);

	int GetID();
	string GetIndustrialProtocol();
	string GetTrasportProtocol();
	string GetIpAddress();
	int GetPort();

	map<unsigned short, AnalogInput*> GetAnalogInputList();
	map<unsigned short, AnalogOutput*> GetAnalogOutoputList();
	map<unsigned short, DigitalDevice*> GetDigitalDevices();

	void AddAnalogInput(AnalogInput* analogInput);
	void AddAnalogOutput(AnalogOutput* analogOutput);
	void AddDigitalDevice(DigitalDevice* digitalDevice);
	
	unsigned short GetIncrementValue(unsigned short address);

	SocketStruct* GetSocket();
};
