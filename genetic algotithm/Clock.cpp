#include "Clock.h"


Clock::Clock(void)
{
	time = 0;
	PCFreq = 0.0;
	CounterStart = 0;
}

Clock::~Clock(void)
{

}

void Clock::startTimer()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

void Clock::endTimer()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	time = double(li.QuadPart - CounterStart) / PCFreq;
}

double Clock::ReturnTime()
{
	return time;
}