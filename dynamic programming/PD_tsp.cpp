#include "stdafx.h"
#include "PD_tsp.h"


/******************************************************************************************
																						  *		
					 	          PROGRAMOWANIE DYNAMICZNE                                *  
																						  *
*******************************************************************************************/

PD_tsp::PD_tsp(void)
{
	rozmiar = 0 ;
	koszt = 1000000;
	macierz.resize(rozmiar);
	droga.resize(rozmiar);
	odwiedzone = new(nothrow) bool[rozmiar];
		
		for(int i = 0; i < rozmiar; i++)
		{
			odwiedzone[i] = 0;
		}


}

//---------------------------------------------------------------

PD_tsp::PD_tsp(string sciezka)
{
	fstream plik;
	plik.open(sciezka, ios::in);
		if(plik.good())
		{
			plik >> rozmiar;
			macierz.resize(rozmiar);
				for(int i=0; i<rozmiar ; i++)
				{
					macierz[i].resize(rozmiar);		
				}

				for(int i=0; i<rozmiar ; i++)
				{
					for(int j=0; j<rozmiar ;j++)
					{
						plik >> macierz[i][j] ;
					}
				}
		}
		else
		{
			cout << "Bledne wczytywanie ... " <<endl;
		}

	droga.resize(macierz.size());
		
		for (int i=0; i < macierz.size(); i++)
		{
			droga[i] = i;
		}

	odwiedzone = new(nothrow) bool[rozmiar];
		
		for(int i = 0; i < rozmiar; i++)
		{
			odwiedzone[i] = 0;
		}
	

}

//---------------------------------------------------------------

PD_tsp::PD_tsp(int **matrix, int n)
{
	rozmiar = n;
	macierz.resize(rozmiar);
		for(int i=0; i<rozmiar ; i++)
		{
			macierz[i].resize(rozmiar);		
		}

	droga.resize(macierz.size());
		for(int i=0; i < macierz.size(); i++)
		{
			droga[i] = i;
		}

		for(int i=0; i<macierz.size(); i++)
		{
			for(int j=0; j<macierz.size(); j++)
			{
				macierz[i].at(j) = matrix[i][j];
			}
		}

	odwiedzone = new(nothrow) bool[rozmiar];
		
		for(int i = 0; i < rozmiar; i++)
		{
			odwiedzone[i] = 0;
		}

}

//---------------------------------------------------------------

PD_tsp::PD_tsp(int n)
{
	rozmiar = n;
	macierz.resize(rozmiar);
		for(int i=0; i<rozmiar ; i++)
		{
			macierz[i].resize(rozmiar);		
		}

	droga.resize(macierz.size());
		for(int i=0; i < macierz.size(); i++)
		{
			droga[i] = i;
		}

		for(int i=0; i<macierz.size(); i++)
		{
			for(int j=0; j<macierz.size(); j++)
			{
				if(i != j )
				{
					macierz[i].at(j) = rand() % 30 ;
				}
				else
				{
					macierz[i].at(j) = 0;
				}
			}
		}

	odwiedzone = new(nothrow) bool[rozmiar];
		
		for(int i = 0; i < rozmiar; i++)
		{
			odwiedzone[i] = 0;
		}

}

//---------------------------------------------------------------

int PD_tsp::Algorytm_dynamiczny(vector<vector<int>> &macierz, vector<int> &droga, int start)
{

	int minkoszt;						 /* Najnizszy koszt. */
	int biezkoszt;						 /* Biezacy koszt. */
	vector <int> temp(macierz.size());	 /* Tymczasowa zmienna pomocnicza. */
	vector <int> mindroga(macierz.size());

	/* Warunek konczacy rekurencje. */
		if (start == macierz.size() - 2)
		{
			return macierz[droga[macierz.size()-2]][droga[macierz.size()-1]] + macierz[droga[macierz.size()-1]][0];
		}
	
	/* Obliczanie drogi rozpoczynajacej sie w punkcie startu. */
	minkoszt = 999;
		for (int i = start+1; i < macierz.size(); i++)
		{ 
	
				for (int j=0; j < macierz.size(); j++)
				{
					temp[j] = droga[j];
				}
 
	/* Wyregulowanie danych . */
			temp[start+1] = droga[i];
			temp[i] = droga[start+1];
				
	/* Znaleziono lepsza droge ? uruchomienie rekurencji  */
				if (macierz[droga[start]][droga[i]] + (biezkoszt = Algorytm_dynamiczny(macierz, temp, start+1)) < minkoszt) 
				{
					minkoszt = macierz[droga[start]][droga[i]] + biezkoszt;
						for (int k=0; k < macierz.size(); k++)
						{
							mindroga[k] = temp[k];
						}
				}
		}
 
	/* Ustawienie minimalnej sciezki. */
		for (int i=0; i < macierz.size(); i++)
		{
			droga[i] = mindroga[i];
		}

	return minkoszt;
}

//---------------------------------------------------------------

void PD_tsp::Rozwiaz_TSP_PD()
{
	koszt = Algorytm_dynamiczny(macierz, droga, 0);	
}

//---------------------------------------------------------------

void PD_tsp::Wyswietl_macierz()
{
	cout << "Macierz kosztow : " << endl;

		for(int i=0; i<macierz.size(); i++)
		{
				for(int j=0; j<macierz.size(); j++)
				{
					if(macierz[i].at(j) == 999)
					{
					    cout << "inf  ";
					}
					else
					{
						cout << macierz[i].at(j) << "  ";
					}
				}

			cout << endl;
		}
}

//---------------------------------------------------------------

void PD_tsp::Wyswietl_rozwiazanie()
{
	cout<<"\nProgramowanie dynamiczne:\n";
	cout << "Minimalny koszt drogi:  " <<  koszt;
	cout << endl;
	cout << "Droga: " ;
		for (int i=0; i< macierz.size() ; i++)
		{
			cout << droga[i]+1 << "  ";
		}
	cout << "1\n";
	cout << endl;
}

//---------------------------------------------------------------

PD_tsp::~PD_tsp(void)
{
}

//---------------------------------------------------------------


/******************************************************************************************
																						  *		
									PRZEGLAD ZUPE£NY                                      *  
																						  *
*******************************************************************************************/

void PD_tsp::Permutacje(int n, int k, int &min, int start)
{
	int i;
		if(k == 0 && tab[0] == start)
		{
			tab[rozmiar] = tab[0];
			Testuj_droge(min);
		}
		else
		{
				for(i = k-1; i >= 0; i--)
				{
					Zamien(k, i);
					Permutacje( n, k-1, min ,start);
					Zamien( k, i);
				}

		}
}

//----------------------------------------------------------------

void PD_tsp::Usun_tab_odp()
{
	tab.clear();
	odp.clear();
}

//----------------------------------------------------------------

void PD_tsp::Usun_odwiedzone()
{
	for(int i = 0; i < rozmiar; i++)
		odwiedzone[i] = false;	
}

//----------------------------------------------------------------

void PD_tsp::Testuj_droge(int &m)
{
	koszt = 0;
	int i = 0;
	bool all = false;
	int aktualny = tab[i];
	int nastepny = tab[i+1];
		
		while(!all)
		{
				if(macierz[aktualny][nastepny] < 1000000)
					koszt += macierz[aktualny][nastepny];
			odwiedzone[aktualny] = true;
			int temp = 0;
			for(int j = 0; j < rozmiar; j++)
				if(!odwiedzone[j])
					temp++;
			if(temp == 0)
				all = true;
		
			if(!all)
			{
				aktualny = nastepny;
				i++;
				nastepny = tab[i+1];
			}

		}

		if(koszt < m && koszt != 0)
		{
			m = koszt;
			odp = tab;
		}

	Usun_odwiedzone();
}

//----------------------------------------------------------------

void PD_tsp::Zamien(int k, int i)
{
	int temp = tab[k-1];
	tab[k-1] = tab[i];
    tab[i] =  temp;
}

//----------------------------------------------------------------

void PD_tsp::Przeglad_zupelny()
{
	
	int n;
	int min = 1000000;
	n = rozmiar;
	tab.resize(n + 1);
	odp.resize(n + 1);
	int start;
	start = 0;

	for(int i = 0; i < n; i++)
		tab[i] = i;
		
	Permutacje(n, n, min, start);
	koszt = min;
	
}

//----------------------------------------------------------------

void PD_tsp::Wyswietl_rozwiazanie_PZ()
{
	cout<<"\nPrzeglad zupelny:\n";
	cout << "Minimalny koszt drogi: " << koszt << endl;
	cout<<"Droga:";
	
		for(int i = 0; i < rozmiar; i++)
		{
			cout << odp[i] +1 <<"  ";
		}
	cout << odp[rozmiar] +1<< endl;
	cout << endl;
	cout << endl;
	
	Usun_odwiedzone();
	Usun_tab_odp();
}

//----------------------------------------------------------------