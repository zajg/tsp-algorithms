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
    bool operator()( wezel a, wezel b)
    {
        return a.bound > b.bound;
    }
};


//Klasa Komiwojazer
class Komiwojazer{

	private:
            int liczbaMiast;
            int** macierz;
            int* najlepszeZupelny;
            int najlepszyKoszt;
            int kosztZupelny(int T[]);

            bool check(wezel a, int i); //funkcja pomocnicza do wyszukania danych w wektorze (B&B)
            bool check2(wezel a, int i); //funkcja pomocnicza do wyszukania danych w wektorze (B&B)
                
            void swap(int &a, int &b); //funkcja zamieniajaca dwa elementy tablicy miejsca (Przeglad)
            void permutacje(int T[], int ix); //funkcja wyznaczajaca permutacje (Przeglad

	public:
            Komiwojazer(); //konstruktor
            ~Komiwojazer();	//destruktor

            int bound(wezel a); //funkcja wyznaczajaca ograniczenie dla wezla (B&B)
	    int length(wezel a); //funkcja wyznaczajaca dlugosc sciezki jaka trzeba przebyc do wezla (B&B)

            void przegladZupelny(); //przeglad zupelny 


            void wyswietlMacierz(); //metoda wyswietlajaca macierz
            void boundBranch(); //dziel i ograniczaj

	
};
