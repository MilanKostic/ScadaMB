#include <iostream>
#include "ClientHandler.h"
#include "Socket.h"

int main()
{
	Socket::Instance();

	ClientHandler::Instance()->ServerThread("9000");
	return 0;
}