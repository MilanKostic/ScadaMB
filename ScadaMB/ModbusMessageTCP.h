#pragma once


enum ModbusMessageTypes
{
	READ_COILS = 0x01,
	READ_DESCRETE_INPUTS = 0x02,
	READ_HOLDING_REGISTERS = 0x03,
	READ_INPUT_REGISTERS = 0x04,
	WRITE_SINGLE_COIL = 0x05,
	WRITE_SINGLE_REGISTER = 0x06
};

#pragma pack(1)
typedef struct {
	unsigned short transactionIdentifier;
	unsigned short protocolIdentifier;
	unsigned short length;
	char unitIdentifier;
}Header;

class ModbusMessageTCP
{
protected:
	Header header;
	char functionCode;
	int messageLength;
public:
	virtual char* Serialize();
	virtual int GetMessageLength();
};
