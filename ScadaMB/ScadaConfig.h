#pragma once

#include "RTDB.h"

class ScadaConfig
{
private:

public:
	ScadaConfig();
	void LoadScadaParams(RTDB* realTimeDatabase);
};