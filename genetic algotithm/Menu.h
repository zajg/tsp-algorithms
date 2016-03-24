#pragma once

#include "TravelingSalesmanProblem.h"
#include "GeneticAlgorithm.h"

class Menu
{
private:

	GeneticAlgorithm sa;
	TravelingSalesmanProblem tsp;
	void readCitiesMatrixFromKeyboard();
	void readCitiesMatrixFromFile();
	void printCitiesMatrix();
	void startAlgorithm();
	//void startAlgorithmStepByStep();
	void startMeasurements();
	void measurePS(std::string matrix_file_name);
	void measureGC(std::string matrix_file_name);
	void measureMP(std::string matrix_file_name);
	
public:
	
	Menu();
	~Menu();
	void start();
	void startAlgorithmStepByStep();
};

