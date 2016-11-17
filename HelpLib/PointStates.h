#pragma once
enum PointState {
	Off = 0x0001,
	On = 0x1000,
	Progress = 0x0000,
	Error = 0x0101
};


enum PointStatus {
	OnScan = 0,
	OffScan,
	Broken,
	Stale,
	Commanding
};
