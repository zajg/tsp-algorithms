#include "stdafx.h"
#include "Zegar.h"


Zegar::Zegar(void)
{
	time=0;
	PCFreq = 0.0;
	CounterStart = 0;
}

Zegar::~Zegar(void)
{

}

void Zegar::startTimer()
{
	LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";
 
    PCFreq = double(li.QuadPart)/1000.0;
 
    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

void Zegar::endTimer()
{
	LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    time=double(li.QuadPart-CounterStart)/PCFreq;
}

double Zegar::ReturnTime()
{
	return time;
}