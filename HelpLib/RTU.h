#pragma once
#include <iostream>
#include <string>

enum PointStatus {
	OnScan = 0,
	OffScan,
	Broken,
	Stale,
	Commanding
};

using namespace std;

class RTU {
private:
	int id;
	string industrialProtocol;
	string transportProtocol;
	string ipAddress;
	int port;

public:
	RTU(int id, string industrialProtocol, string transportProtocol, string ipAddress, int port);
	
	void SetIndustrialProtocol(string protocol);
	void SetTransportProtocol(string protocol);

	int GetID();
	string GetIndustrialProtocol();
	string GetTrasportProtocol();
	string GetIpAddress();
	int GetPort();
};
