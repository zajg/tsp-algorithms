#pragma once
#include "stdafx.h"  
#include <windows.h>

class Zegar
{
	double PCFreq ;
	__int64 CounterStart ;
	double time;

	public:
	
		Zegar(void);
		~Zegar(void);
		void startTimer();
		void endTimer();
		double ReturnTime();
 
};

