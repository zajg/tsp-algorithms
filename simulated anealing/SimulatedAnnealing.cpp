
#include "SimulatedAnnealing.h"
#include <algorithm>
#include <iostream>
#include <ctime>

SimulatedAnnealing::SimulatedAnnealing(TravelingSalesmanProblem& t) :
tsp(t)
{
}


SimulatedAnnealing::~SimulatedAnnealing()
{
}

void SimulatedAnnealing::startAlgorithm(float _delta, int _itr_for_one_temp, float _final_temperature)
{
	if (tsp.getCitiesCount() == 0) return;
	srand(time(NULL));
	
	int current_cost;
	int new_cost;
	std::vector <int> current_solution(generateRandomSolution());
	current_cost = countCost(current_solution);
	std::vector <int> new_solution;

	float current_temperature;
	float delta = 0;
	float temp_delta;

	for (int i = 1; i < std::pow(tsp.getCitiesCount(), 2); i++)
	{
		new_solution = generateRandomSolution();
		new_cost = countCost(new_solution);
		temp_delta = new_cost - current_cost;
		if (temp_delta > delta)
		{
			delta = temp_delta;
		}
		current_solution = new_solution;
		current_cost = new_cost;
	}
	current_temperature = delta;
	delta = _delta;
	
	the_best_solution = current_solution;
	min_cost = current_cost;
	while (current_temperature > _final_temperature)
	{
		for (int i = 0; i <_itr_for_one_temp; i++){
			new_solution = current_solution;
			swapTwoRandomCities(new_solution);
			new_cost = countCost(new_solution);
			if (new_cost < current_cost)
			{
				current_solution = new_solution;
				current_cost = new_cost;
				if (new_cost < min_cost)
				{
					the_best_solution = new_solution;
					min_cost = new_cost;
				}
			}
			else
			{
				float r = float(rand() % 101) / 100.0f;
				float p = countProbability(current_cost, new_cost, current_temperature);
				if (r < p)
				{
					current_solution = new_solution;
					current_cost = new_cost;
				}
			}
		}
		current_temperature *= delta;
	}
	
}

std::vector <int> SimulatedAnnealing::generateRandomSolution()
{
	std::vector <int> solution;
	for (int i = 0; i < tsp.getCitiesCount(); i++)
	{
		solution.push_back(i);
	}
	std::random_shuffle(solution.begin(), solution.end());
	return solution;
}

int SimulatedAnnealing::countCost(std::vector<int> path)
{
	int cost = 0;
	for (std::size_t i = 0; i < path.size() - 1; i++)
	{
		cost += tsp.getEdgeCost(path[i], path[i + 1]);
	}
	cost += tsp.getEdgeCost(path[path.size() - 1], path[0]);

	return cost;
}

void SimulatedAnnealing::swapTwoRandomCities(std::vector<int>& path)
{
	int firstPosition = rand() % path.size();

	int secondPosition;
	do {
		secondPosition = rand() % path.size();
	} while (firstPosition == secondPosition);

	int buffor = path[firstPosition];
	path[firstPosition] = path[secondPosition];
	path[secondPosition] = buffor;
}

float SimulatedAnnealing::countProbability(int current_cost, int new_cost, float current_temperature)
{
	return std::powf(2.7182818f, -(float(new_cost - current_cost) / current_temperature));
}

void SimulatedAnnealing::startAlgorithmStepByStep()
{
	if (tsp.getCitiesCount() == 0) return;

	srand(time(NULL));

	int current_cost;
	int new_cost;

	std::cout << std::endl << "Wyznaczenie pierwszego rozwi¹zania przez losowanie...." << std::endl;

	std::vector <int> current_solution(generateRandomSolution());
	current_cost = countCost(current_solution);
	the_best_solution = current_solution;
	min_cost = current_cost;

	std::cout << std::endl << getSolutionToString(current_solution, current_cost) << std::endl;

	std::vector <int> new_solution;

	float current_temperature;
	float delta = 0;
	float temp_delta;

	std::cout << std::endl << "Wyznaczenie temperatury poczatkowej...." << std::endl;

	for (int i = 1; i < std::pow(tsp.getCitiesCount(), 2); i++)
	{
		new_solution = generateRandomSolution();
		new_cost = countCost(new_solution);
		temp_delta = new_cost - current_cost;
		if (temp_delta > delta)
		{
			delta = temp_delta;
		}
		current_solution = new_solution;
		current_cost = new_cost;
	}
	current_temperature = delta;
	delta = 0.999f;

	std::cout << std::endl << "Temperatura poczatkowa: " << current_temperature << std::endl;
	std::cout << std::endl << "Wspolczynnik schladzania: " << delta << std::endl;

	float end_temperature = 0.5f;

	std::cout << std::endl << "Temperatura koncowa: " << end_temperature << std::endl;
	
	while (current_temperature > end_temperature)
	{
		new_solution = current_solution;
		swapTwoRandomCities(new_solution);
		new_cost = countCost(new_solution);

		std::cout << std::endl << "Nowe rozwiazanie: ";
		std::cout << std::endl << getSolutionToString(new_solution, new_cost) << std::endl;

		if (new_cost < current_cost)
		{
			current_solution = new_solution;
			current_cost = new_cost;
			if (new_cost < min_cost)
			{
				the_best_solution = new_solution;
				min_cost = new_cost;
			}
		}
		else
		{
			float r = float(rand() % 101) / 100.0f;
			std::cout << std::endl << "Losowa liczba z przedzialu [0,1]: ";
			std::cout << std::endl << r << std::endl;

			float p = countProbability(current_cost, new_cost, current_temperature);

			std::cout << std::endl << "Wartosc prawdopodobienstwa: ";
			std::cout << std::endl << p << std::endl;

			if (r < p)
			{
				current_solution = new_solution;
				current_cost = new_cost;
			}
		}

		std::cout << std::endl << "Aktualnie najlepsze rozwiazanie:";
		std::cout << std::endl << getSolutionToString(current_solution, current_cost) << std::endl;

		std::cout << std::endl << "Schladzanie..." << std::endl;
		current_temperature *= delta;
		std::cout << std::endl << "Aktualna temperatura: " << current_temperature << std::endl;
		std::cout << min_cost << std::endl;
	}

	std::cout << std::endl << "Najlepsze rozwiazanie:";
	std::cout << std::endl << getSolutionToString(the_best_solution, min_cost) << std::endl;

}

std::string SimulatedAnnealing::getSolutionToString(std::vector<int> path, int cost)
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