#pragma once
#include "PointAddress.h"
#include <iostream>
#include "RTU.h"
#include <list>

class RTDB {
private:
	static RTDB *instance;
	list<RTU> listOfRemotes;

public:
	static RTDB *Instance();
	char *GetCurrentValues();
};