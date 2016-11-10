#pragma once

class PointAddress {

public:
	const static unsigned int ventilVode = 0x0001;
	const static unsigned int ventilPeska = 0x0002;
	const static unsigned int ventilSljunka = 0x0003;
	const static unsigned int dozvolaPraznjenjaMjesalice = 0x0004;

	const static unsigned int kolicinaVodeOut = 0x0005;
	const static unsigned int kolicinaPijeskaOut = 0x0006;
	const static unsigned int kolicinaSljunkaOut = 0x0007;
};