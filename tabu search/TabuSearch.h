#pragma once
#include "TravelingSalesmanProblem.h"
#include <string>
#include <vector>
#include <list>

class TabuSearch
{
	std::list<std::pair<int, int> > tabu_list;
	int countCost(std::vector<int> path);
	TravelingSalesmanProblem& tsp;
	float countProbability(int current_cost, int new_cost, float current_temperature);
public:
	TabuSearch(TravelingSalesmanProblem& tsp);
	~TabuSearch();

	std::string getSolutionToString(std::vector<int> path, int cost);
	std::pair<int, int> swapTwoRandomCities(std::vector<int>& path);
	std::vector <int> generateRandomSolution();
	void startAlgorithm(int tabu_list_size = 10, int neighbours_count = 400, int steps_without_change = 100, int steps_with_random_neighbourhood = 20);
	//void startAlgorithmStepByStep();
	bool checkTabu(std::pair<int, int>&, std::vector<int>& path, int neighbour_cost);

	std::vector< int > the_best_solution;
	int min_cost;
};