
#include "TabuSearch.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include <limits>

TabuSearch::TabuSearch(TravelingSalesmanProblem& t) :
tsp(t)
{
}


TabuSearch::~TabuSearch()
{
}

void TabuSearch::startAlgorithm(int tabu_list_size, int neighbours_count, int steps_without_change, int steps_with_random_neighbourhood)
{
	//std::cout << "parameters:" << tabu_list_size << "," << neighbours_count << "," << steps_without_change << "," << steps_with_random_neighbourhood << "\n";
	if (tsp.getCitiesCount() == 0) return;
	srand(static_cast<unsigned int>(time(NULL)));
	
	int current_cost;
	std::vector <int> current_solution(generateRandomSolution());
	current_cost = countCost(current_solution);

	the_best_solution = current_solution;
	min_cost = current_cost;

	std::pair<int, int> swaped_cities;
	std::pair<int, int> saved_swap;
	
	std::vector <int> the_best_neighbour;
	std::vector <int> neighbour;
	int neighbour_cost;
	int the_best_neighbour_cost;
	int steps = 0;
	int change_neighbourhood_count = 0;
	do {
		the_best_neighbour_cost = std::numeric_limits<int>::max();
		for (int i = 0; i < neighbours_count; i++)
		{
			neighbour = current_solution;
			swaped_cities = swapTwoRandomCities(neighbour);
			neighbour_cost = countCost(neighbour);
			if (neighbour_cost < the_best_neighbour_cost && checkTabu(swaped_cities, neighbour, neighbour_cost))
			{
				the_best_neighbour_cost = neighbour_cost;
				the_best_neighbour = neighbour;
				saved_swap = swaped_cities;
			}
		}
		current_solution = the_best_neighbour;
		current_cost = the_best_neighbour_cost;
		

		if (current_cost < min_cost)
		{
			the_best_solution = current_solution;
			min_cost = current_cost;
			steps = 0;
		}

		if (tabu_list.size() > tabu_list_size)
		{
			tabu_list.pop_front();
		}
		tabu_list.push_back(saved_swap);
		steps++;
		if (steps > steps_without_change)
		{
			current_solution = generateRandomSolution();
			current_cost = countCost(current_solution);
			change_neighbourhood_count++;
			steps = 0;
		}
		

	} while (change_neighbourhood_count < steps_with_random_neighbourhood);
}

std::vector <int> TabuSearch::generateRandomSolution()
{
	std::vector <int> solution;
	for (int i = 0; i < tsp.getCitiesCount(); i++)
	{
		solution.push_back(i);
	}
	std::random_shuffle(solution.begin(), solution.end());
	return solution;
}

int TabuSearch::countCost(std::vector<int> path)
{
	int cost = 0;
	for (std::size_t i = 0; i < path.size() - 1; i++)
	{
		cost += tsp.getEdgeCost(path[i], path[i + 1]);
	}
	cost += tsp.getEdgeCost(path[path.size() - 1], path[0]);

	return cost;
}

std::pair<int, int> TabuSearch::swapTwoRandomCities(std::vector<int>& path)
{
	int firstPosition = rand() % path.size();

	int secondPosition;
	do {
		secondPosition = rand() % path.size();
	} while (firstPosition == secondPosition);

	std::pair<int, int> swaped_cities;

	if (firstPosition > secondPosition)
	{
		swaped_cities.first = path.at(secondPosition);
		swaped_cities.second = path.at(firstPosition);
	}
	else
	{
		swaped_cities.first = path.at(firstPosition);
		swaped_cities.second = path.at(secondPosition);
	}

	int buffor = path.at(firstPosition);
	path.at(firstPosition) = path.at(secondPosition);
	path.at(secondPosition) = buffor;
	
	return swaped_cities;
}

bool TabuSearch::checkTabu(std::pair<int, int>& swaped_cities, std::vector<int>& path, int neighbour_cost)
{
	std::list<std::pair<int, int> >::iterator list_iterator = tabu_list.begin();
	while (list_iterator != tabu_list.end())
	{
		if (swaped_cities.first == list_iterator->second || swaped_cities.second == list_iterator->first)
		{
			int first_element_index = std::find(path.begin(), path.end(), list_iterator->first) - path.begin();
			int second_element_index = std::find(path.begin(), path.end(), list_iterator->second) - path.begin();
			if (first_element_index < second_element_index && neighbour_cost > min_cost)
				return false;
		}
		list_iterator++;
	}
	return true;
}

std::string TabuSearch::getSolutionToString(std::vector<int> path, int cost)
{
	std::string str = "";
	str.append("Koszt przejscia sciezki:\n");
	str.append(std::to_string(cost));
	str.append("\nSciezka:\n");
	for (std::size_t i = 0; i < path.size(); i++)
	{
		str.append(std::to_string(path[i]));
		str.append(" ");
	}

	return str;
}


