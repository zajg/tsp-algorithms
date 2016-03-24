#ifndef UTWORZ_DANE_CPP
#define UTWORZ_DANE_CPP

#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

void generujKomiwojazer(int iloscMiast)
{
	srand(time(NULL));
	
	fstream plik;
	plik.open("dane", ios::out);
	
	
	if(!plik.good())
	{
		cout << "Nie można utworzyć pliku z danymi" << endl;
		return;
	}
	else
	{
		plik << iloscMiast << endl;

                int** macierz = new int*[iloscMiast];
                for(int i = 0; i < iloscMiast; i++)
                {
                    macierz[i] = new int[iloscMiast];
                }

                for(int i = 0; i < iloscMiast; i++)
                {
                    for(int j = i; j < iloscMiast; j++)
                    {
                        if(i == j)
                        {
                            macierz[i][j] = -1;
                        }
                        else
                        {
                            int temp = rand() % 50 + 1;
                            macierz[i][j] = temp;
                            macierz[j][i] = temp;
                        }
                    }
                }

                for(int i = 0; i < iloscMiast; i++)
                {
                    for(int j = 0; j < iloscMiast; j++)
                    {
                        plik << macierz[i][j] << " ";
                    }
                    plik << endl;
                }

                for(int i = 0; i < iloscMiast; i++)
                {
                    delete [] macierz[i];
                }

                delete [] macierz;

	}

	plik.close();

	return;
}

#endif
