#pragma once

#include "TravelingSalesmanProblem.h"
#include "TabuSearch.h"

class Menu
{
private:

	TabuSearch sa;
	TravelingSalesmanProblem tsp;
	void readCitiesMatrixFromKeyboard();
	void readCitiesMatrixFromFile();
	void printCitiesMatrix();
	void startAlgorithm();
	//void startAlgorithmStepByStep();
	void startMeasurements();
	void measureTLS(std::string);
	void measureNC(std::string);
	void measureSWC(std::string);
	void measureSWRN(std::string);
	void measureST();
	
public:
	
	Menu();
	~Menu();
	void start();
};

