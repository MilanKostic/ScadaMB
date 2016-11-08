#pragma once
#include "ModbusMessageTCP.h"

enum ErrorMessageCode
{
	CODE_01 = 0x01,
	CODE_02 = 0x02,
	CODE_03 = 0x03,
	CODE_04 = 0x04
};

class ErrorMessage : ModbusMessageTCP
{
private:
	ErrorMessageCode errorCode;
public:
	ErrorMessage(char* bytes);
	void ErrorMessage::Deserialize(char* bytes);
};