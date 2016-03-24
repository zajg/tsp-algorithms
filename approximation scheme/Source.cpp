#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Komiwojazer.h"
#include "Clock.h"


#define MX 10000 //bardzo duza liczba potrzebna do wag

using namespace std;


struct KrawedzCyklu{
	int pocz;
	int kon;
	float waga;
};



int main()
{
	float graf[100][100]; // graf nad ktorym bedziemy pracowac
	int odwiedzone[MX]; //tablica odwiedzonych
	float waga[MX];       //tablica wag poszczegolnych polaczen
	int nastepnik[MX];  // tablica nastepnych polaczen
	int krawedzieMST[MX][2];  // tablica krawedzi MST
	vector <KrawedzCyklu> krawedzieCyklu;  // tablica krawedzi cylku
	vector <int> wierzcholkiCyklu;  // tablica krawedzi cylku
	vector <int> trasa;  // tablica z trasa komiwojazera

	int n, m;      //n - liczba wierzkochlkow   m - liczba krawedzi
	int a, b; 
	float c, koszt;        // dane wejsciowe a- pierwszy wierzcholek, b- drugi wierzcholek, c - waga
	int wiersz, wierzcholki, i;


	int liczbaMiast;
	float** macierz;



	char wybor = 'n';
	cout << "Czy wygenerowac nowe dane? t/n\n";
	cin >> wybor;

	if (wybor == 't'){

		int wybor = 5;
		cout << "\nPodaj liczbe miast ?\n";
		cin >> wybor;
		//if (wybor > 13) wybor = 13;
		if (wybor < 3) wybor = 3;

		int* mx = new int[wybor];
		int* my = new int[wybor];

		srand(time(NULL));

		for (int i = 0; i < wybor; i++){
			mx[i] = rand() % 100;
			my[i] = rand() % 100;
		}

		fstream plikB;

		//zapisujemy
		plikB.open("dane.txt", ios::out);

		plikB << wybor << endl; //zapisanie liczby miast


		for (int i = 0; i < wybor; i++)
		{
			for (int j = 0; j < wybor; j++)
			{
				if (i == j) plikB << 0 << " ";
				else plikB << sqrt((mx[j] - mx[i])*(mx[j] - mx[i]) + (my[j] - my[i])*(my[j] - my[i])) << " ";
			}
			plikB << endl;
		}

		plikB.close();
		//zapisujemy koniec


		delete[] mx;
		delete[] my;


	}



	fstream plikA;
	plikA.open("dane.txt", ios::in);

	plikA >> liczbaMiast; //wczytanie liczby miast

	macierz = new float*[liczbaMiast]; //alokacja pamieci na macierz sasiedztwa

	for (int i = 0; i < liczbaMiast; i++)
	{
		macierz[i] = new float[liczbaMiast];
		for (int j = 0; j < liczbaMiast; j++)
		{
			plikA >> macierz[i][j];
		}
	}

	plikA.close();
	//wczytujemy koniec


	//zapisujemy
	plikA.open("dane_pomocnicze.txt", ios::out);

	plikA << liczbaMiast << " " << (liczbaMiast*(liczbaMiast - 1)) / 2 << endl; //zapisanie liczby miast


	for (int i = 0; i < liczbaMiast - 1; i++)
	{
		for (int j = i + 1; j < liczbaMiast; j++)
		{
			plikA << i << " " << j << " " << macierz[i][j] << endl;
		}
	}

	plikA.close();
	//zapisujemy koniec

		fstream plik;
		plik.open("dane_pomocnicze.txt", ios::in);

		plik >> n;								
		plik >> m;

		for (int e = 0; e < n; e++) //inicjalizacja danych
		{
			nastepnik[e] = odwiedzone[e] = 0; //nie ma poprzednikow i nastepnikow
			waga[e] = MX; // waga jest rowna max
			for (int r = 0; r < n; r++)
			{
				graf[e][r] = 0; // wypelnianie tablicy zerami
			}
		}

		for (int q = 0; q < m; q++) //pobieranie  drog w grafie
		{
			plik >> a;
			plik >> b;
			plik >> c;
			
			graf[a][b] = graf[b][a] = c; //wypelnianie tablicy danymi uzytkownika
		}


		cout << "Macierz grafu:" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << graf[i][j] << "\t";
			}
			cout << endl << endl;
		}

		Clock clock; //tworzymy obiekt klasy zegar
		double time; //tworzymy zmienna do przetrzymywania zmierzonego czasu
		clock.startTimer();



		// inicjalizacja danych do algorytmu Prima
		wiersz = 1; //zaczynamy od pierwszego wiersza, czyli przeszukujemy wszystkie polaczenia pierwszego wierzcholka
		waga[wiersz] = 0; // pierwsza waga rowna jest zero
		wierzcholki = 1; //zaczynamy od pierwszech wierzcholka
		odwiedzone[wiersz] = 1; // pierwszy wierzcholek odwiedzilismy, bo zaczynamy od niego

		//algorytm Prima
		while (wierzcholki != n)  // n liczba wierzcholkow
		{
			for (i = 0; i<n; i++)//przeszukanie pierwszego wiersza
			{
				if (graf[wiersz][i] != 0)//jezeli nie ma polaczenia z wierzcholkien to nie wchodz
				{
					if (odwiedzone[i] == 0)// jezeli byl odiweczony to nie wchodz
					{
						if (waga[i]>graf[wiersz][i])// jezeli jest droga  o mniejszym koszcie to nie wchodz
						{
							waga[i] = graf[wiersz][i]; // znaleziono najtansza droge, podmiana za wczesniejsze							
							krawedzieMST[i][0] = wiersz;
							krawedzieMST[i][1] = i;							
						}
					}
				}
			}

			
			koszt = MX; // maksymalny koszt
			for (i = 0; i<n; i++) // zanotowanie  wagi w tabilcy
			{
				if (odwiedzone[i] == 0) // sprawdzenie czy byl odwiedzony
				{
					if (waga[i]<koszt) // sprawdzenie czy waga jest nizsza od maxa
					{
						koszt = waga[i]; // ustawienie nowej wagi  jako koszt
						wiersz = i; // ustawienie wiersza w ktorym zmienilem wage
					}
				}
			}
			
			odwiedzone[wiersz] = 1; // odwiedzony wierzcholek
			wierzcholki++; // przechodzimy do nstepnego wierzcholka
		}

		koszt = 0; //koszty na poczatku rowne zero
		for (i = 0; i<n; i++) // dodaje wagi
		{
			koszt += waga[i]; //suma wag
		}



		//wyswietlenie wynikow
		cout << "\nSuma wag MST:\n";
		cout << koszt << "\n\n"; 
		cout << "\nKrawedzie MST:\n";
		for (i = 0; i<n; i++) 
		{
			if (krawedzieMST[i][0] >= 0) cout << krawedzieMST[i][0] << " -> " << krawedzieMST[i][1] << " ";
			if (waga[i] > 0) cout << "[" << waga[i] << "]" << endl;
		}

		for (i = 0; i<n; i++)
		{
			if (krawedzieMST[i][0] >= 0){
				KrawedzCyklu tmp;
				tmp.pocz = krawedzieMST[i][0];
				tmp.kon = krawedzieMST[i][1];
				tmp.waga = waga[i];
				krawedzieCyklu.push_back(tmp);

				tmp.kon = krawedzieMST[i][0];
				tmp.pocz = krawedzieMST[i][1];
				tmp.waga = waga[i];
				krawedzieCyklu.push_back(tmp);
			}
		}

		cout << "\nKrawedzie Cylku:\n";
		for (size_t i = 0; i < krawedzieCyklu.size(); i++) 
			cout << krawedzieCyklu[i].pocz << " -> " << krawedzieCyklu[i].kon << " [" << krawedzieCyklu[i].waga << "]" <<endl;


		//wyznaczanie kolejnosci wierzcholkow w cyklu na podstawie podwojonych krawedzi mst
		int aktualny = krawedzieCyklu[i].pocz;
		wierzcholkiCyklu.push_back(aktualny);
		
		while (!krawedzieCyklu.empty()){
			for (int i = 0; i < krawedzieCyklu.size(); i++){
				if (krawedzieCyklu[i].pocz == aktualny){		
					aktualny = krawedzieCyklu[i].kon;
					wierzcholkiCyklu.push_back(aktualny);
					krawedzieCyklu.erase(krawedzieCyklu.begin() + i);
				}
			}
		}


		//wyswietlenir kolejnych wierzchlkow cyklu
		cout << "\nWierzcholki Cylku:\n";
		for (size_t i = 0; i < wierzcholkiCyklu.size(); i++)
			cout << wierzcholkiCyklu[i] << " -> ";


		//zamiana cyklu na trase moniwojazera poprzez wyeliminowanie powtorzen elementow w cylku
		for (size_t i = 0; i < wierzcholkiCyklu.size(); i++)
			if (std::find(trasa.begin(), trasa.end(), wierzcholkiCyklu[i]) == trasa.end())
				trasa.push_back(wierzcholkiCyklu[i]);
		

		//wyswietlenie kolejnych wierzcholkow trasy
		cout << "\n\nTrasa komiwojazera wyznaczona schematem aproksymacyjnym:\n";
		for (size_t i = 0; i < trasa.size(); i++)
			cout << trasa[i] << " -> ";
			cout << trasa[0] << " ";


		//obliczenie dlugosci trasy
		cout << "\n\nKoszt trasy komiwojazera wyznaczony schematem aproksymacyjnym:\n";
		float kosztSA = 0;
		for (int i = 0; i < trasa.size() - 1; i++){
			kosztSA += graf[trasa[i]][trasa[i+ 1]];
		}
		kosztSA += graf[trasa[trasa.size() - 1]][trasa[0]];
		cout << kosztSA;
		
		cout << "\n\nCzas wykonania schematu aproksymacyjnyego:\n";
		clock.endTimer();
		time = clock.ReturnTime();
		cout << time << endl;
		

		//rozwiazanie przy pomocy przegladu zupelnego
		Komiwojazer *komi = new Komiwojazer();
		cout << "\n\nTrasa komiwojazera wyznaczona przegladem zupelnym:\n";
		clock.startTimer();
		komi->przegladZupelny();

		cout << "\n\nCzas wykonania przegladu zupelnego:\n";
		clock.endTimer();
		time = clock.ReturnTime();
		cout << time << endl;


	int x;
	cin >> x;

	return 0;
}