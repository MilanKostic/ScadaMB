#pragma once
enum PointState {
	Off = 0,
	On,
	Progress,
	Error
};


enum PointStatus {
	OnScan = 0,
	OffScan,
	Broken,
	Stale,
	Commanding
};
