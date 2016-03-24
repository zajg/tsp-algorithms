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
int Komiwojazer::kosztZupelny(int T[])
{
    int koszt = 0;

    for(int i = 0; i < liczbaMiast-1; i++)
    {
        //pobieranie dlugosci odleglosci z macierzy odleglosci
        koszt += macierz[T[i]][T[i+1]];
    }

    //trzeba zamknac cykl Hamiltona i ostatni element polaczyc z pierwszym
    koszt += macierz[T[liczbaMiast-1]][T[0]];

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
  if( ix < liczbaMiast-1 ) 
  { 
    for(int i = ix; i < liczbaMiast; i++)
    {
      swap(T[ix], T[i]); // zamienia dwa elementy miejscami
      permutacje(T, ix+1);
      swap(T[ix], T[i]); // przywracamy
    }
  }
  else
  {
      //po otrzymaniu permutacji, trzeba wyznaczyc jej koszt
      //i porownac z dotychczasowym najlepszym kosztem
      int tempKoszt = kosztZupelny(T);

      if(tempKoszt < najlepszyKoszt)
      {
          for(int i = 0; i < liczbaMiast; i++)
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

    for(int i = 0; i < liczbaMiast; i++)
    {
        tablica[i]  = i;
    }

    permutacje(tablica, 0);

    for(int i = 0; i < liczbaMiast; i++)
    {
        cout << najlepszeZupelny[i] << " ";
    }
    cout << " <==== " << najlepszyKoszt << endl;

    delete [] tablica;

}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Komiwojazer
 *  Description:  Konstruktor klasy komiwojazer
 * =====================================================================================
 */
Komiwojazer::Komiwojazer():
	macierz(NULL),
        najlepszeZupelny(NULL)
{
    //otwarcie pliku do odczytu
	fstream plik;
	plik.open("dane", ios::in);
	
	plik >> liczbaMiast; //wczytanie liczby miast
	
	macierz = new int*[liczbaMiast]; //alokacja pamieci na macierz sasiedztwa
	
	for(int i = 0; i < liczbaMiast; i++)
	{
		macierz[i] = new int[liczbaMiast];
		for(int j = 0; j < liczbaMiast; j++)
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
	if(macierz != NULL)
	{
		for(int i = 0; i < liczbaMiast; i++)
		{
			delete [] macierz[i];			
		}		
		
		delete [] macierz;
		macierz = NULL;
	}

        if(najlepszeZupelny != NULL)
        {
            delete [] najlepszeZupelny;
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
	if(macierz != NULL)
	{
		   for(int i = 0; i < liczbaMiast; i++)
		   {
		   		for(int j = 0; j < liczbaMiast; j++)
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



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  length
 *  Description:  Funkcja wyznaczajaca dlugosc trasy jaka trzeba pokonac od korzenia
 *  do wezla podanego jako argument funkcji
 * =====================================================================================
 */
int Komiwojazer::length(wezel a)
{
    int length = 0; //inicjalizacja dlugosci
    
        //sprawdzenie odleglosci przez cala zapisana sciezke
    for(int i = 0; i < a.path.size() - 1; i++)
    {
        length += macierz[a.path[i]][a.path[i+1]];
    }

    return length;

}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  check
 *  Description:  Funkcja pomocnicza sprawdzajaca czy wezel podany jako argument
 *  posiada w swojej sciezce wierzcholek o numerze "i" podany jako drugi argument
 *  Akcja wykonuje sie dla pierwszych n-1 wierzcholkow ze sciezki path
 * =====================================================================================
 */
bool Komiwojazer::check(wezel a, int i)
{
        for(int z = 0; z < a.path.size() - 1; z++)
        {
            if(i == a.path[z])
            {
                return true;
            }
        }
        
        return false;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  check
 *  Description:  Funkcja pomocnicza sprawdzajaca czy wezel podany jako argument
 *  posiada w swojej sciezce wierzcholek o numerze "i" podany jako drugi argument
 *  Akcja wykonuje sie dla ostatnich n-1 wierzcholkow ze sciezki path
 * =====================================================================================
 */
bool Komiwojazer::check2(wezel a, int i)
{
        for(int z = 1; z < a.path.size(); z++)
        {
            if(i == a.path[z])
            {
                return true;
            }
        }

        return false;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bound
 *  Description:  Funkcja wyznaczajaca dolne ograniczenie 
 * =====================================================================================
 */
int Komiwojazer::bound(wezel a)
{
    int bound = length(a); //dolne ograniczenie sklada sie z dotychczasowej dlugosci


    for(int i = 0; i < liczbaMiast; i++)
    {
        //sprawdzenie czy bylismy juz w jakims wierzcholku i
        //aby nie liczyc minimum dla wierzcholkow juz odwiedzonych
        //BLOKOWANIE niepotrzebnych wierszy macierzy
        if(check(a, i))
        {
            continue;
        }

        int minimum = INT_MAX;
        for(int j = 0; j < liczbaMiast; j++)
        {
            //BLOKOWANIE niepotrzebnych kolumn macierzy
            if(check2(a, j))
            {
                continue;
            }

            //BLOKOWANIE przejscia do samego siebie
            if(i == j)
            {
                continue;
            }

            //blokowanie zamkniecia cyklu przedwczesnie
            if(a.path[a.path.size()-1] == i && j == 0)
            {
                continue;
            }

            //wyznaczanie minimum z przefiltrowanego wiersza
            if(macierz[i][j] < minimum && macierz[i][j] > 0)
            {
                minimum = macierz[i][j];
            }
        }

        if(minimum != INT_MAX)
        {
            bound += minimum;
        }
    }

    return bound;
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  boundBranch
 *  Description:  glowny algorytm podzialu i ograniczen
 * =====================================================================================
 */
void Komiwojazer::boundBranch()
{
    wezel u,v; //pomocnicze wezly
    std::vector<int> temp; //sciezka tymczasowa
    std::vector<int> sciezka; //sciezka koncowa, do ktorej zostanie wpisane rozwiazanie

    //inicjalizacja wezla v wartosciami poczatkowymi. Zawsze zaczynamy od wezla 0
    temp.push_back(0);
    v.bound = 0;
    v.level = 0;
    v.path = temp;
    v.bound = bound(v);

    //inicjalizacja wezla u wartosciami poczatkowymi
    u.bound = 0;
    u.level = 0;

    //stworzenie kolejki priorytetowej
    std::priority_queue < wezel, std::vector<wezel>, wezelPorownanie > kolejka;
    
    //na poczatku minimalna dlugosc trasy jest nieskonczona
    int minLength = INT_MAX;

    //wrzucamy do kolejki pierwszy wierzcholek
    kolejka.push(v);

    //dopoki kolejka zawiera w sobie wierzcholki trwa algorytm
    while(!kolejka.empty())
    {
        //zdejmowanie z kolejki wierzcholka w celu wykonywania na nim dzialan
        v = kolejka.top();
        kolejka.pop();

        //sprawdzenie czy znaleziono lepsze ograniczenie
        if(v.bound < minLength)
        {
            //przejscie do kolejnego poziomu rozpatrywanego drzewa
            u.level = v.level + 1;

            //tworzenie mozliwych permutacji zbioru rozwiazan
            for(int i = 1; i < liczbaMiast; i++)
            {
                //jesli wierzcholka nie znaleziono w sciezce dotychczasowych rozwiazan
                if(std::find(v.path.begin(), v.path.end(), i) == v.path.end())
                {
                    //dolozenie znalezionego 'wolnego' wierzcholka
                    u.path = v.path;
                    u.path.push_back(i);
                    
                    if(u.level == liczbaMiast - 2)
                    {
                        for(int j = 1; j < liczbaMiast; j++)
                        {
                            if(std::find(u.path.begin(), u.path.end(), j) == u.path.end())
                            {
                                //dolozenie do sciezki ostatniego nieodwiedzonego miasta
                                u.path.push_back(j);
                                break;
                            }
                        }

                        //dolozenie na koniec sciezko 0, aby wrocic do poczatku 
                        //(nie jest konieczne, ale ulatwia wyznaczanie dlugosci sciezki)
                        u.path.push_back(0);

                        if(length(u) < minLength)
                        {
                            minLength = length(u);
                            sciezka = u.path;
                        }
                    }
                    else
                    {
                        //wyznaczenie ograniczenia w przypadku gdy nie jest to konczenie 
                        //sprawdzania sciezki
                        u.bound = bound(u);
                        
                        //jesli rozwiazanie jest "obiecujaca", to wrzucamy do kolejki
                        if(u.bound < minLength)
                        {
                            kolejka.push(u);
                        }
                    }
                }
            }
        }
    }

    //wyswietlenie znalezionego rozwiazania
    for(int i = 0; i < sciezka.size(); i++)
    {
        cout << sciezka[i] << " ";
    }
    //wyswietlenie rozmiaru znalezionego rozwiazania
    u.path = sciezka;
    cout << " <=== " << length(u) << endl;
}
