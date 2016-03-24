#include "stdafx.h"
#include "PD_tsp.h"
#include "Zegar.h"

void Info()
{
}

void Przejscie()
{
	//cout << "Wcisnij enter aby przejsc dalej..." << endl;
	//cin.get();
	//cin.get();
	//system("cls");
}

void Menu()
{
	cout << "Menu:" << endl;
	cout << "1. Sprawdzenie poprawnosci zaimplementowanego algorytmu. " << endl;
	cout << "2. Wykonywanie pomiarow. " << endl;
	cout << "3. Koniec." <<endl;
	cout << "" << endl;
	cout << "Wybor: ";
}

void Menu_programu()
{

	cout << endl << "Sposob wprowadzenia danych:" << endl;
	cout << "1. Wczytaj z klawiatury." << endl;
	cout << "2. Wczytaj z pliku." << endl;
	cout << "3. Wygeneruj losowe dane." << endl;
	cout << "4. Powrot." <<endl;
	cout << "" << endl;
	cout << "Wybor: ";
}

void Wybierz_algorytm()
{
	cout << endl << "Wybor algorytmu:" << endl;
	cout << "1. Programowanie dynamiczne" << endl;
	cout << "2. Przeglad zupelny." << endl;
	cout << "3. Powrot." <<endl;
	cout << "" << endl;
	cout << "Wybor: ";

}

int Spytaj_o_rozmiar()
{
	int n;
	cout << "Prosze podaj ilosc miast : " ;
	cin >> n;
	return n;
}

void Spytaj_o_dane(int **m, int r)
{
	cout << endl << "Prosze podawac dane :" << endl;

		for(int i = 0 ; i < r ; i++)
		{
				for(int j = 0 ; j < r ; j++)
				{
					cout << "Macierz[" << i << "][" << j << "]=  ";
					cin >> m[i][j];
				}
		}

}

string Spytaj_o_sciezke()
{
	string s;
	cout << endl << "Prosze podac nazwe pliku do wczytania lub dokladna sciezke: " ;
	cin >> s;
	return s;
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	Info();
	PD_tsp *problem = 0;
	fstream plik, plik2;
	int n ;
	Zegar clock;
	double czas;
	string sciezka = " ";
	int **mac=0;
	char wybor = '3', wybor_2 = '4', wybor_3='3';
		do{
				Przejscie();
				Menu();
				cin >> wybor;

						switch(wybor)
						{
							case '1':		do{
													Przejscie();
													Menu_programu();
													cin >> wybor_2;
														
															switch(wybor_2)
															{

																case '1':	n = Spytaj_o_rozmiar();
																			mac = new int*[n];

																				for(int i = 0; i < n ; i++)
																				{
																					mac[i] = new int[n];
																				}

																			Spytaj_o_dane(mac, n);
																			problem = new PD_tsp(mac,n);
																			break;

																case '2':	sciezka = Spytaj_o_sciezke();
																			problem = new PD_tsp(sciezka);
																			break;

																case '3':	n = Spytaj_o_rozmiar();
																			problem = new PD_tsp(n);
																			break;

																case '4':	cout << "Powrot do poprzedniegu menu..." << endl;
																			break;

																default:	cout << "Sprobuj jeszcze raz , dokonales zlego wyboru..." << endl;
																			break;

															}


															if(wybor_2 > '0' && wybor_2 < '4')
															{
																do{
																	Przejscie();
																	Wybierz_algorytm();
																	cin >> wybor_3;
																			
																			switch(wybor_3)
																			{

																				case '1':   //problem->Wyswietl_macierz();
																							problem->Rozwiaz_TSP_PD();
																							problem->Wyswietl_rozwiazanie();
																							break;

																				case '2':	//problem->Wyswietl_macierz();
																							problem->Przeglad_zupelny();
																							problem->Wyswietl_rozwiazanie_PZ();
																							break;

																				case '3':	cout << "Powrot do poprzedniegu menu..." << endl;
																							break;

																				default:	cout << "Sprobuj jeszcze raz , dokonales zlego wyboru..." << endl;
																							break;

																			}

																}while(wybor_3 !='3');
															}
											}while(wybor_2 != '4');
								
										break;

							case '2':	cout << "Podaj liczbe N-miast: ";
										cin >>n;
										plik.open("PD.txt", ios::app);
										plik << n << endl;
										plik2.open("PZ.txt", ios::app);
										plik2 << n << endl;
											for(int i = 0 ; i < 10; i++)
											{
												problem = new PD_tsp(n);
												clock.startTimer();
												problem ->Rozwiaz_TSP_PD();
												clock.endTimer();
												czas = clock.ReturnTime();
												problem->Wyswietl_rozwiazanie();
												plik << czas << endl;
											}
											for(int i=0; i < 10 ; i++)
											{
												problem = new PD_tsp(n);
												clock.startTimer();
												problem->Przeglad_zupelny();
												clock.endTimer();
												czas = clock.ReturnTime();
												problem->Wyswietl_rozwiazanie_PZ();
												plik2 << czas << endl;
											}
										plik.close();
										plik2.close();
										break;

							case '3':	cout << "Koniec działania programu..." << endl;
										break;

							default:	cout << "Sprobuj jeszcze raz , dokonales zlego wyboru..." << endl;
										break;
						
						}

		}while(wybor !='3');

		if(mac!= 0)
		{
			for(int i=0 ; i < n; i++)
			{
				delete []mac[i];
			}

			delete []mac;
		}
	return 0;
}
