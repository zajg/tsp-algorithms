#include "komiwojazer.h"

#include <iostream>
#include <fstream>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;


/*
* ===  FUNCTION  ======================================================================
*         Name:  kosztZupelny
*  Description:  Funkcja wyznaczajaca zupelny koszt danej permutacji (Przeglad zupelny)
* =====================================================================================
*/
float Komiwojazer::kosztZupelny(int T[])
{
	float koszt = 0;

	for (int i = 0; i < liczbaMiast - 1; i++)
	{
		//pobieranie dlugosci odleglosci z macierzy odleglosci
		koszt += macierz[T[i]][T[i + 1]];
	}

	//trzeba zamknac cykl Hamiltona i ostatni element polaczyc z pierwszym
	koszt += macierz[T[liczbaMiast - 1]][T[0]];

	return koszt;
}


/*
* ===  FUNCTION  ======================================================================
*         Name:  swap
*  Description:  Funkcja pomocnicza zamieniajaca miejscami dwa elementy (Przeglad zupelny)
* =====================================================================================
*/
void Komiwojazer::swap(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}


/*
* ===  FUNCTION  ======================================================================
*         Name:  permutacje
*  Description:  Funkcja pomocnicza wyznaczajaca wszystkie permutacje elementow tablicy
*  podanej jako argument
* =====================================================================================
*/
void Komiwojazer::permutacje(int T[], int ix)
{
	if (ix < liczbaMiast - 1)
	{
		for (int i = ix; i < liczbaMiast; i++)
		{
			swap(T[ix], T[i]); // zamienia dwa elementy miejscami
			permutacje(T, ix + 1);
			swap(T[ix], T[i]); // przywracamy
		}
	}
	else
	{
		//po otrzymaniu permutacji, trzeba wyznaczyc jej koszt
		//i porownac z dotychczasowym najlepszym kosztem
		float tempKoszt = kosztZupelny(T);

		if (tempKoszt < najlepszyKoszt)
		{
			for (int i = 0; i < liczbaMiast; i++)
			{
				najlepszeZupelny[i] = T[i];
			}
			najlepszyKoszt = tempKoszt;
		}
	}
}


/*
* ===  FUNCTION  ======================================================================
*         Name:  przegladZupelny
*  Description:  funkcja wyznaczajaca najlepsza trase przy pomocy przegladu zupelnego
*  wyswietla najlepsza permutacje oraz jej koszt
* =====================================================================================
*/
void Komiwojazer::przegladZupelny()
{
	int* tablica = new int[liczbaMiast];

	for (int i = 0; i < liczbaMiast; i++)
	{
		tablica[i] = i;
	}

	permutacje(tablica, 0);

	for (int i = 0; i < liczbaMiast; i++)
	{
		cout << najlepszeZupelny[i] << " -> ";
	}
	cout << najlepszeZupelny[0];
	cout << "\n\nKoszt trasy komiwojazera wyznaczony przegladem zupelnym:\n";
	cout << najlepszyKoszt << endl;

	delete[] tablica;

}


/*
* ===  FUNCTION  ======================================================================
*         Name:  Komiwojazer
*  Description:  Konstruktor klasy komiwojazer
* =====================================================================================
*/
Komiwojazer::Komiwojazer() :
macierz(NULL),
najlepszeZupelny(NULL)
{
	//otwarcie pliku do odczytu
	fstream plik;
	plik.open("dane.txt", ios::in);

	plik >> liczbaMiast; //wczytanie liczby miast

	macierz = new float*[liczbaMiast]; //alokacja pamieci na macierz sasiedztwa

	for (int i = 0; i < liczbaMiast; i++)
	{
		macierz[i] = new float[liczbaMiast];
		for (int j = 0; j < liczbaMiast; j++)
		{
			plik >> macierz[i][j];
		}
	}

	plik.close();

	najlepszeZupelny = new int[liczbaMiast];
	najlepszyKoszt = INT_MAX;
}



/*
* ===  FUNCTION  ======================================================================
*         Name:  ~Komiwojazer
*  Description:  Destruktor klasy komiwojazer
* =====================================================================================
*/
Komiwojazer::~Komiwojazer()
{
	if (macierz != NULL)
	{
		for (int i = 0; i < liczbaMiast; i++)
		{
			delete[] macierz[i];
		}

		delete[] macierz;
		macierz = NULL;
	}

	if (najlepszeZupelny != NULL)
	{
		delete[] najlepszeZupelny;
	}
}



/*
* ===  FUNCTION  ======================================================================
*         Name:  wyswietlMacierz
*  Description:  Funkcja wyswietlajaca dostepna w pamieci macierz
* =====================================================================================
*/
void Komiwojazer::wyswietlMacierz()
{
	if (macierz != NULL)
	{
		for (int i = 0; i < liczbaMiast; i++)
		{
			for (int j = 0; j < liczbaMiast; j++)
			{
				cout << macierz[i][j] << "\t";
			}
			cout << endl;
		}
	}
	else
	{
		cout << "Nie ma co wyswietlic!" << endl;
	}
}



