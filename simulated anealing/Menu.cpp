
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
	sa.startAlgorithm(0.9999 , 10, 0.5);
	std::cout << std::endl << sa.getSolutionToString(sa.the_best_solution, sa.min_cost) << std::endl;
}


void Menu::startAlgorithmStepByStep()
{
	sa.startAlgorithmStepByStep();
}

void Menu::startMeasurements()
{
	measureItr();
	//measureFinalTemp();
	//measureDelta();

}

void Menu::measureItr(){

	std::cout << "rozpoczynam pomiary";

	std::string matrix_file_name = "ftv55.atsp"; //ustalamy nazwe pliku wejsciowego

	tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name); //wczytujemy instancje problemu

	Clock clock; //tworzymy obiekt klasy zegar
	double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu

	std::string file_name = "D://wyniki_i_" + matrix_file_name + ".csv"; //ustalamy nazwe pliku wyjsciowego
	std::fstream file;

	file.open(file_name, std::ios::out);
	file << "itr_for_one_temp" << " ; " << "avg_solution" << " ; " << "median_solution" << " ; " << "time" << std::endl; //nazywamy kolumny

	float delta = 0.9; //ustalamy parametry poczatkowe algorytmu
	int itr_for_one_temp = 1;
	float final_temp = 0.1;

	const int number_of_measurements = 10; //ustalamy ilosc eksperymentow

	long float times = 0;
	long float solutions = 0;
	long float solutions_array[number_of_measurements];

	for (int p = 3; itr_for_one_temp <= 600; itr_for_one_temp += p){

		times = solutions = 0;

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(delta, itr_for_one_temp, final_temp); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << itr_for_one_temp << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku
		if (itr_for_one_temp>30) itr_for_one_temp += 2;
	}

	file.close();


}


void Menu::measureFinalTemp(){

	std::string matrix_file_name = "ftv55.atsp"; //ustalamy nazwe pliku wejsciowego

	tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name); //wczytujemy instancje problemu

	Clock clock; //tworzymy obiekt klasy zegar
	double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu

	std::string file_name = "D://wyniki_final_temp_" + matrix_file_name + ".csv"; //ustalamy nazwe pliku wyjsciowego
	std::fstream file;

	file.open(file_name, std::ios::out);
	file << "final_temp" << " ; " << "avg_solution" << " ; " << "median_solution" << " ; " << "time" << std::endl; //nazywamy kolumny

	double delta = 0.9; //ustalamy parametry poczatkowe algorytmu
	int itr_for_one_temp = 30;
	float final_temp = 1500;

	const int number_of_measurements = 6; //ustalamy ilosc eksperymentow

	long float times = 0;
	long float solutions = 0;
	long float solutions_array[number_of_measurements];

	for (float p = 0.85; final_temp >= 0.1; final_temp *= p){
		times = solutions = 0;

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(delta, itr_for_one_temp, final_temp); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << final_temp << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku
		//if (itr_for_one_temp>30) itr_for_one_temp += 2;
	}

	file.close();


}


void Menu::measureDelta(){

	std::cout << "rozpoczynam pomiary";

	std::string matrix_file_name = "ftv55.atsp"; //ustalamy nazwe pliku wejsciowego

	tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name); //wczytujemy instancje problemu

	Clock clock; //tworzymy obiekt klasy zegar
	double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu

	std::string file_name = "D://wyniki_delta_" + matrix_file_name + ".csv"; //ustalamy nazwe pliku wyjsciowego
	std::fstream file;

	file.open(file_name, std::ios::out);
	file << "delta" << " ; " << "avg_solution" << " ; " << "median_solution" << " ; " << "time" << std::endl; //nazywamy kolumny

	double delta = 0.9999; //ustalamy parametry poczatkowe algorytmu
	int itr_for_one_temp = 60;
	float final_temp = 0.1;

	const int number_of_measurements = 5; //ustalamy ilosc eksperymentow

	long float times = 0;
	long float solutions = 0;
	long float solutions_array[number_of_measurements];

	for (float p = 0.95; delta >= 0.4; ){
		times = solutions = 0;

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(delta, itr_for_one_temp, final_temp); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << delta << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku
		//if (itr_for_one_temp>30) itr_for_one_temp += 2;

		if (delta < 0.99)delta *= p;
		else delta *= 0.995;
	}

	file.close();


}