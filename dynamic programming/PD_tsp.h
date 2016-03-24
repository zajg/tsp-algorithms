#pragma once
class PD_tsp
{
	private:

		int rozmiar;						/* Liczba miast . */
		vector <vector<int>> macierz;		/* Macierz kosztów. */
		vector <int> droga;					/* Droga - przechowuje indeksy wszystkich wierzcholkow . */
		int koszt;							/* Najmniejszy koszt. */
		int Algorytm_dynamiczny(vector<vector<int>> &macierz, vector<int> &droga, int start);
		

		int rozwiazanie;
		vector <int> tab, odp;
		bool *odwiedzone;
		
//-------------------------------------------------------------------------
//      FUNKCJE DO PRZEGLADU ZUPE£NEGO
//-------------------------------------------------------------------------
		void Permutacje(int n, int k, int &min, int start);
		void Usun_odwiedzone();
		void Usun_tab_odp();
		void Testuj_droge(int &m);
		void Zamien(int k, int i);

	public:
		PD_tsp(void);
		PD_tsp(string sciezka);
		PD_tsp(int **matrix, int n);
		PD_tsp(int n);
		void Rozwiaz_TSP_PD();
		void Przeglad_zupelny();
		void Wyswietl_macierz();
		void Wyswietl_rozwiazanie();
		void Wyswietl_rozwiazanie_PZ();
		~PD_tsp(void);
};

