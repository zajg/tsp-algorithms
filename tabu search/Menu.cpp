
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
				//startAlgorithmStepByStep();
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
	sa.startAlgorithm();
	std::cout << std::endl << sa.getSolutionToString(sa.the_best_solution, sa.min_cost) << std::endl;
}


// void Menu::startAlgorithmStepByStep()
// {
// 	sa.startAlgorithmStepByStep();
// }

void Menu::startMeasurements()
{
	measureST();

	std::string instance_name = "br17";
	/*
	measureTLS(instance_name);
	measureNC(instance_name);
	measureSWC(instance_name);
	measureSWRN(instance_name);
	
	std::cout << "zakonczono etap 1.\n";
	instance_name = "ftv33";

	measureTLS(instance_name);
	measureNC(instance_name);
	measureSWC(instance_name);
	measureSWRN(instance_name);
	
	std::cout << "zakonczono etap 2\n";
	instance_name = "p43";

	measureTLS(instance_name);
	measureNC(instance_name);
	measureSWC(instance_name);
	measureSWRN(instance_name);

	std::cout << "zakonczono etap 3\n";
	instance_name = "ftv55";

	measureTLS(instance_name);
	measureNC(instance_name);
	measureSWC(instance_name);
	measureSWRN(instance_name);
	
	instance_name = "ftv170";

	measureTLS(instance_name);
	measureNC(instance_name);
	measureSWC(instance_name);
	measureSWRN(instance_name);
	*/
}

void Menu::measureTLS(std::string matrix_file_name){

	//system("cls");

	tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

	Clock clock; //tworzymy obiekt klasy zegar
	double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu

	std::string file_name = "D://wyniki_tls_" + matrix_file_name + ".csv"; //ustalamy nazwe pliku wyjsciowego
	
	std::fstream file;
	file.open(file_name, std::ios::out);
	file << "tabu_list_size" << " ; " << "avg_solution" << " ; " << "median_solution" << " ; " << "time" << std::endl; //nazywamy kolumny

	//ustalamy parametry poczatkowe algorytmu
	int tabu_list_size = 15;
	int neighbours_count = 100;
	int steps_without_change = 15;
	int steps_with_random_neighbourhood = 10;
	
	/*
	//rozpoczynamy pomiar
	clock.startTimer(); //rozpoczynamy pomiar czasu
	sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
	clock.endTimer(); //konczymy pomiar czasu
	time = clock.ReturnTime(); //zachowyjemy czas
	std::cout << std::endl << sa.getSolutionToString(sa.the_best_solution, sa.min_cost) << std::endl << "Czas: " << std::endl << time << std::endl<<std::endl; //wyswietlamy wyniki
	*/

	
	//ustalamy ilosc eksperymentow
	const int number_of_measurements = 5; 

	long float times = 0;
	long float solutions = 0;
	long float solutions_array[number_of_measurements];

	for (tabu_list_size = 5; tabu_list_size <= 200; tabu_list_size += 5){

		times = solutions = 0;

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << tabu_list_size << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku
		//if (tabu_list_size>20) tabu_list_size += 1;
	}

	file.close();
	

}

void Menu::measureNC(std::string matrix_file_name){

	//system("cls");

	tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

	Clock clock; //tworzymy obiekt klasy zegar
	double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu

	std::string file_name = "D://wyniki_nc_" + matrix_file_name + ".csv"; //ustalamy nazwe pliku wyjsciowego

	std::fstream file;
	file.open(file_name, std::ios::out);
	file << "neighbours_count" << " ; " << "avg_solution" << " ; " << "median_solution" << " ; " << "time" << std::endl; //nazywamy kolumny

	//ustalamy parametry poczatkowe algorytmu
	int tabu_list_size = 35;
	int neighbours_count = 100;
	int steps_without_change = 15;
	int steps_with_random_neighbourhood = 10;

	
	//ustalamy ilosc eksperymentow
	const int number_of_measurements = 5;

	long float times = 0;
	long float solutions = 0;
	long float solutions_array[number_of_measurements];

	for (neighbours_count = 5; neighbours_count <= 1000; neighbours_count += 5){

		times = solutions = 0;

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << neighbours_count << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku
		if (neighbours_count>100) neighbours_count += 10;
		if (neighbours_count>500) neighbours_count += 10;
	}

	file.close();


}

void Menu::measureSWC(std::string matrix_file_name){

	//system("cls");

	tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

	Clock clock; //tworzymy obiekt klasy zegar
	double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu

	std::string file_name = "D://wyniki_swc_" + matrix_file_name + ".csv"; //ustalamy nazwe pliku wyjsciowego

	std::fstream file;
	file.open(file_name, std::ios::out);
	file << "steps_without_change" << " ; " << "avg_solution" << " ; " << "median_solution" << " ; " << "time" << std::endl; //nazywamy kolumny

	//ustalamy parametry poczatkowe algorytmu
	int tabu_list_size = 35;
	int neighbours_count = 100;
	int steps_without_change = 15;
	int steps_with_random_neighbourhood = 10;


	//ustalamy ilosc eksperymentow
	const int number_of_measurements = 5;

	long float times = 0;
	long float solutions = 0;
	long float solutions_array[number_of_measurements];

	for (steps_without_change = 5; steps_without_change <= 400; steps_without_change += 4){

		times = solutions = 0;

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << steps_without_change << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku
		if (steps_without_change>100) steps_without_change += 4;
	}

	file.close();


}

void Menu::measureSWRN(std::string matrix_file_name){

	//system("cls");

	tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

	Clock clock; //tworzymy obiekt klasy zegar
	double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu

	std::string file_name = "D://wyniki2_swrn_" + matrix_file_name + ".csv"; //ustalamy nazwe pliku wyjsciowego

	std::fstream file;
	file.open(file_name, std::ios::out);
	file << "steps_with_random_neighbourhood" << " ; " << "avg_solution" << " ; " << "median_solution" << " ; " << "time" << std::endl; //nazywamy kolumny

	//ustalamy parametry poczatkowe algorytmu
	int tabu_list_size = 25;
	int neighbours_count = 80;
	int steps_without_change = 6;
	int steps_with_random_neighbourhood = 4;


	//ustalamy ilosc eksperymentow
	const int number_of_measurements = 5;

	long float times = 0;
	long float solutions = 0;
	long float solutions_array[number_of_measurements];

	for (steps_with_random_neighbourhood = 1; steps_with_random_neighbourhood <= 600; steps_with_random_neighbourhood += 5){

		times = solutions = 0;

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << steps_with_random_neighbourhood << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku
		if (steps_with_random_neighbourhood>200) steps_with_random_neighbourhood += 10;
	}

	file.close();


}

void Menu::measureST(){

	//system("cls");

	

	Clock clock; //tworzymy obiekt klasy zegar
	double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu

	std::string file_name = "D://wyniki_size-time_.csv"; //ustalamy nazwe pliku wyjsciowego

	std::fstream file;
	file.open(file_name, std::ios::out);
	file << "size" << " ; " << "avg_solution" << " ; " << "median_solution" << " ; " << "time" << std::endl; //nazywamy kolumny

	//ustalamy parametry poczatkowe algorytmu
	int tabu_list_size = 25;														
	int neighbours_count = 80;														
	int steps_without_change = 6;													
	int steps_with_random_neighbourhood = 4;										
																					
																					
	//ustalamy ilosc eksperymentow													
	const int number_of_measurements = 5;											
																					
	long float times = 0;
	long float solutions = 0;
	long float solutions_array[number_of_measurements];

	std::string matrix_file_name = "br17";
	tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << matrix_file_name << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku


		matrix_file_name = "ftv33";
		tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << matrix_file_name << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku

	
		matrix_file_name = "p43";
		tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << matrix_file_name << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku



		matrix_file_name = "ftv55";
		tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << matrix_file_name << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku



		matrix_file_name = "ftv70";
		tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << matrix_file_name << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku



		matrix_file_name = "kro124p";
		tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << matrix_file_name << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku



		matrix_file_name = "ftv170";
		tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << matrix_file_name << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku



		matrix_file_name = "rbg323";
		tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << matrix_file_name << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku



		matrix_file_name = "rbg403";
		tsp.readCitiesDataFromFileToCitiesMatrix(matrix_file_name + ".atsp"); //wczytujemy instancje problemu

		for (int i = 0; i < number_of_measurements; i++)
		{
			clock.startTimer(); //rozpoczynamy pomiar czasu
			sa.startAlgorithm(tabu_list_size, neighbours_count, steps_without_change, steps_with_random_neighbourhood); //wywolujemy algorytm
			clock.endTimer(); //konczymy pomiar czasu
			time = clock.ReturnTime();
			solutions += sa.min_cost;
			times += time;
			solutions_array[i] = sa.min_cost;
		}
		std::sort(std::begin(solutions_array), std::end(solutions_array));

		file << matrix_file_name << " ; " << solutions / number_of_measurements << " ; " << solutions_array[number_of_measurements / 2] << " ; " << times / number_of_measurements << std::endl; //zapisujemy wyniki do pliku




	file.close();


}
