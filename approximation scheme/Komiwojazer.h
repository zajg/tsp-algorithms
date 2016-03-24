#pragma once
#include <vector>

//struktura pomocnicza wezla, reprezentujaca pojedynczy wezel w drzewie poszukiwan
struct wezel
{
	int level; //poziom drzewa
	std::vector <int> path; //dotychczasowa sciezka od korzenia
	int bound; //wyliczone ograniczenie przy pomocy funkcji ograniczen
};

//struktura pomocnicza, ktora umozliwi umieszczenie struktury wezel w kolejce priorytetowej
struct wezelPorownanie
{
	bool operator()(wezel a, wezel b)
	{
		return a.bound > b.bound;
	}
};


//Klasa Komiwojazer
class Komiwojazer{

private:
	int liczbaMiast;
	float** macierz;
	int* najlepszeZupelny;
	float najlepszyKoszt;
	float kosztZupelny(int T[]);

	void swap(int &a, int &b); //funkcja zamieniajaca dwa elementy tablicy miejsca (Przeglad)
	void permutacje(int T[], int ix); //funkcja wyznaczajaca permutacje (Przeglad

public:
	Komiwojazer(); //konstruktor
	~Komiwojazer();	//destruktor

	void przegladZupelny(); //przeglad zupelny 


	void wyswietlMacierz(); //metoda wyswietlajaca macierz


};
