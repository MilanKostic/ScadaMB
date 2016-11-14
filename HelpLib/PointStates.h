#pragma once
enum PointState {
	Off = 0x0000,
	On = 0xff00,
	Progress = 0xffff,
	Error = 0x00ff
};


enum PointStatus {
	OnScan = 0,
	OffScan,
	Broken,
	Stale,
	Commanding
};
