#pragma once
#include "TravelingSalesmanProblem.h"
#include <string>
#include <vector>
#include <list>

class GeneticAlgorithm
{
	void addCorrectCityAt(std::pair<std::vector<int>, int> &child, std::pair<std::vector<int>, int> const &parent, int position, int first, int second);
	int countCost(std::vector<int> path);
	std::vector<std::pair<std::vector<int>, int> > crossoverPMX(int population_size, float mutation_probability);
	void mutate(std::pair<std::vector<int>, int>& speciman, float probability);
	int rouletteWheelSelection();
	bool solutionIsUnique(std::pair<std::vector<int>, int> new_solution, std::vector<std::pair<std::vector<int>, int> > population);
	void swapTwoRandomCities(std::vector<int>& path);

	std::vector<std::pair<std::vector<int>, int> > population;
	TravelingSalesmanProblem& tsp;
	
public:
	GeneticAlgorithm(TravelingSalesmanProblem& tsp);
	~GeneticAlgorithm();

	std::string getSolutionToString(std::vector<int> path, int cost);
	
	std::vector <int> generateRandomSolution();
	void startAlgorithm(int population_size, int generation_count, float mutation_probability);

	void startAlgorithmStepByStep();
	
	std::vector< int > the_best_solution;
	int min_cost;
};