
#include "Menu.h"
#include "Clock.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <math.h>

Menu::Menu() :
sa(tsp)
{
}


Menu::~Menu()
{
}

void Menu::start()
{
	tsp.readCitiesDataFromFileToCitiesMatrix("br17.atsp");

	Clock clock;

	//clock.startTimer();
	//sa.startAlgorithm(40, 40, 0.45);
	//clock.endTimer();
	//std::cout << std::endl << clock.ReturnTime() << std::endl << sa.getSolutionToString(sa.the_best_solution, sa.min_cost) << std::endl;
	int choice;
	while (true)
	{
		std::cout << "1. Wczytaj macierz miast z pliku." << std::endl;
		std::cout << "2. Wprowadz macierz miast z klawiatury." << std::endl;
		std::cout << "3. Wyswietl macierz miast." << std::endl;
		std::cout << "4. Uruchom algorytm." << std::endl;
		std::cout << "5. Uruchom algorytm w trybie krok po kroku." << std::endl;
		std::cout << "6. Uruchom algorytm w trybie wykonywania pomiarów." << std::endl;
		std::cout << "0. Zakoncz program.";
		std::cout << std::endl << "Wybierz opcje: ";

		std::cin >> choice;

		std::cout << std::endl << std::endl;

		switch (choice)
		{
			case 1:
				readCitiesMatrixFromFile();
				break;
			case 2:
				readCitiesMatrixFromKeyboard();
				break;
			case 3:
				printCitiesMatrix();
				break;
			case 4:
				startAlgorithm();
				break;
			case 5:
				startAlgorithmStepByStep();
				break;
			case 6:
				startMeasurements();
				break;
			case 0:
				return;
		}
	}
}

void Menu::readCitiesMatrixFromFile()
{
	std::cout << "Podaj sciezke do pliku z macierza miast:\n";
	std::string path;
	std::cin >> path;

	if (tsp.readCitiesDataFromFileToCitiesMatrix(path))
	{
		std::cout << "Pomyslne wczytano macierz miast.\n";
	}
	else
	{
		std::cout << "Nie powiodlo sie wczytywanie macierzy miast z pliku.\n";
	}
}

void Menu::printCitiesMatrix()
{
	std::cout << std::endl << std::endl << tsp.getMatrixToString() << std::endl;
}

void Menu::readCitiesMatrixFromKeyboard()
{
	std::cout << "Podaj ilosc miast:\n";
	std::string cities_count;
	std::cin >> cities_count;
	int cost;
	int matrix_size = atoi(cities_count.c_str());
	tsp.setCitiesCount(matrix_size);

	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 0; j < matrix_size; j++)
		{
			if (i != j)
			{
				std::cout << "Podaj wartosc sciezki z miasta " << i << " do miasta " << j << "\t";
				std::cin >> cost;
				tsp.setEdgeCost(cost, i, j);
			}
				
		}
	}
}

void Menu::startAlgorithm()
{
	sa.startAlgorithm(90, 100, 0.35);
	std::cout << std::endl << sa.getSolutionToString(sa.the_best_solution, sa.min_cost) << std::endl;
}


void Menu::startAlgorithmStepByStep()
{
	sa.startAlgorithmStepByStep();
	std::cout << std::endl << sa.getSolutionToString(sa.the_best_solution, sa.min_cost) << std::endl;
}


void Menu::startMeasurements()
{
	


	std::string instance_name = "br17";
	
	measurePS(instance_name);
	
	measureGC(instance_name);
	
	measureMP(instance_name);
	

	std::cout << "zakonczono etap 1\n";
	instance_name = "ftv33";

	measurePS(instance_name);
	measureGC(instance_name);
	measureMP(instance_name);
	 

	std::cout << "zakonczono etap 2\n";
	instance_name = "p43";

	measurePS(instance_name);
	measureGC(instance_name);
	measureMP(instance_name);
	 

	std::cout << "zakonczono etap 3\n";
	instance_name = "ftv55";

	measurePS(instance_name);
	measureGC(instance_name);
	measureMP(instance_name);
	 
	std::cout << "zakonczono etap 4\n";
	instance_name = "ftv170";

	measurePS(instance_name);
	measureGC(instance_name);
	measureMP(instance_name);

	std::cout << "zakonczono etap 5\n";
	 
	
}

void Menu::measurePS(std::string matrix_file_name){

	//system("cls");

	tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

	Clock clock; //tworzymy obiekt klasy zegar
	double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu

	std::string file_name = "D://wyniki_ps_" + matrix_file_name + ".csv"; //ustalamy nazwe pliku wyjsciowego

	std::fstream file;
	file.open(file_name, std::ios::out);
	file << "population_size" << " ; " << "avg_solution" << " ; " << "median_solution" << " ; " << "time" << std::endl; //nazywamy kolumny

	//ustalamy parametry poczatkowe algorytmu
	int population_size = 5;
	int generation_count = 150;
	float mutation_probability = 0.5;

	/*
	//rozpoczynamy pomiar
	clock.startTimer(); //rozpoczynamy pomiar czasu
	sa.startAlgorithm(population_size, generation_count, mutation_probability); //wywolujemy algorytm
	clock.endTimer(); //konczymy pomiar czasu
	time = clock.ReturnTime(); //zachowyjemy czas
	std::cout << std::endl << sa.getSolutionToString(sa.the_best_solution, sa.min_cost) << std::endl << "Czas: " << std::endl << time << std::endl<<std::endl; //wyswietlamy wyniki
	*/


	//ustalamy ilosc eksperymentow
	const int number_of_measurements = 5;

	long float times = 0;
	long float solutions = 0;
	long float solutions_array[number_of_measurements];

	for (population_size = 2; population_size <= 97; population_size += 2){

		times = solutions = 0;

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(population_size, generation_count, mutation_probability ); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << population_size << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku
		if (population_size>35) population_size += 8;
	}

	file.close();


}

void Menu::measureGC(std::string matrix_file_name){

	//system("cls");

	tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

	Clock clock; //tworzymy obiekt klasy zegar
	double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu

	std::string file_name = "D://wyniki_gc_" + matrix_file_name + ".csv"; //ustalamy nazwe pliku wyjsciowego

	std::fstream file;
	file.open(file_name, std::ios::out);
	file << "generation_count" << " ; " << "avg_solution" << " ; " << "median_solution" << " ; " << "time" << std::endl; //nazywamy kolumny

	//ustalamy parametry poczatkowe algorytmu
	int population_size = 35;
	int generation_count;
	float mutation_probability = 0.5;


	//ustalamy ilosc eksperymentow
	const int number_of_measurements = 5;

	long float times = 0;
	long float solutions = 0;
	long float solutions_array[number_of_measurements];

	for (generation_count = 10; generation_count <= 200; generation_count += 5){

		times = solutions = 0;

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(population_size, generation_count, mutation_probability); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << generation_count << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku
		if (generation_count>100) generation_count += 10;
		if (generation_count>500) generation_count += 10;
	}

	file.close();


}

void Menu::measureMP(std::string matrix_file_name){

	//system("cls");

	tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

	Clock clock; //tworzymy obiekt klasy zegar
	double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu

	std::string file_name = "D://wyniki_mp_" + matrix_file_name + ".csv"; //ustalamy nazwe pliku wyjsciowego

	std::fstream file;
	file.open(file_name, std::ios::out);
	file << "mutation_probability" << " ; " << "avg_solution" << " ; " << "median_solution" << " ; " << "time" << std::endl; //nazywamy kolumny

	//ustalamy parametry poczatkowe algorytmu
	int population_size = 60;
	int generation_count = 150;
	float mutation_probability = 0;


	//ustalamy ilosc eksperymentow
	const int number_of_measurements = 5;

	long float times = 0;
	long float solutions = 0;
	long float solutions_array[number_of_measurements];

	for (mutation_probability = 0; mutation_probability <= 0.9; mutation_probability += 0.05){

		times = solutions = 0;

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(population_size, generation_count, mutation_probability); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << mutation_probability << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku
		if (mutation_probability>100) mutation_probability += 4;
	}

	file.close();


}
