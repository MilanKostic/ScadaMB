#include "ErrorMessage.h"

ErrorMessage::ErrorMessage(char* bytes) : ModbusMessageTCP(bytes) {}

void ErrorMessage::Deserialize(char* bytes)
{
	this->functionCode = bytes[0];
	this->errorCode = (ErrorMessageCode)bytes[1];
}
