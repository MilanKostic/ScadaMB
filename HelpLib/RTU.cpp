#include "RTU.h"

RTU::RTU(int id, string industrialProtocol, string transportProtocol, string ipAddress, int port)
{
	RTU::id = id;
	RTU::industrialProtocol = industrialProtocol;
	RTU::transportProtocol = transportProtocol;
	RTU::ipAddress = ipAddress;
	RTU::port = port;
}

/*RTU::RTU()
{
}*/

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