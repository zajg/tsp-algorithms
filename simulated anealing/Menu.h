#pragma once

#include "TravelingSalesmanProblem.h"
#include "SimulatedAnnealing.h"

class Menu
{
private:

	SimulatedAnnealing sa;
	TravelingSalesmanProblem tsp;
	void readCitiesMatrixFromKeyboard();
	void readCitiesMatrixFromFile();
	void printCitiesMatrix();
	void startAlgorithm();
	void startAlgorithmStepByStep();
	void startMeasurements();
	void measureItr();
	void measureDelta();
	void measureFinalTemp();
	void measureSize();
	
public:
	
	Menu();
	~Menu();
	void start();
};

