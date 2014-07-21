#include "Time.h"

Time::Time()
{
	delta = 0;
	QueryPerformanceFrequency(&frequency);
}

Time::~Time()
{
}

_int64 Time::getTime() const
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return time.QuadPart;
}

double Time::getTimePassedNano(_int64 time1, _int64 time2) const
{
	return (double)((time1 - time2) * SECOND / frequency.QuadPart);
}

double Time::getDelta() const
{
	return delta;
}

void Time::setDelta(double delta)
{
	Time::delta = delta;
}
