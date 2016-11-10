#pragma once
#include <iostream>
#include <string>
#include <list>
//#include "AnalogInput.h"
#include "AnalogOutput.h"
#include "DigitalDevice.h"
using namespace std;

class RTU {
private:
	int id;
	string industrialProtocol;
	string transportProtocol;
	string ipAddress;
	int port;

	list<AnalogInput> analogInputList; 
	list<AnalogOutput> analogOutputList;
	list<DigitalDevice> digitalDevices;

public:
	RTU(int id, string industrialProtocol, string transportProtocol, string ipAddress, int port);
	
	void SetIndustrialProtocol(string protocol);
	void SetTransportProtocol(string protocol);

	int GetID();
	string GetIndustrialProtocol();
	string GetTrasportProtocol();
	string GetIpAddress();
	int GetPort();

	list<AnalogInput> GetAnalogInputList();
	list<AnalogOutput> GetAnalogOutoputList();
	list<DigitalDevice> GetDigitalDevices();
};
