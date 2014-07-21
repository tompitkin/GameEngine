#pragma once

#include <windows.h>

class Time
{
public:
	Time();
	~Time();
	_int64 getTime() const;
	double getDelta() const;
	double getTimePassedNano(_int64 time1, _int64 time2) const;
	void setDelta(double delta);
	static const long SECOND = 1000000000;

private:
	double delta;
	LARGE_INTEGER frequency;
};

