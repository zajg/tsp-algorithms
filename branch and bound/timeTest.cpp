/*
 * =====================================================================================
 *
 *       Filename:  timeTest.cpp
 *
 *    Description:  Metody klasy TimeTest
 *
 *        Version:  1.0
 *        Created:  11.05.2014 01:40:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wojciech Biniek, wojciech.biniek@student.pwr.wroc.pl
 *        Company:  Politechnika Wrocławska
 *
 * =====================================================================================
 */
#ifndef TIME_TEST_CPP
#define TIME_TEST_CPP


#include <iostream>
#include <ctime>

#include "timeTest.h"

#include "utworzDane.cpp"
#include "komiwojazer.cpp"


TimeTest::TimeTest()
{
}


/*-----------------------------------------------------------------------------
 *  POMIARY DLA KOMIWOJAERA
 *-----------------------------------------------------------------------------*/


double TimeTest::czasKomiwojazerZupelny(int rozmiar, int ilePowtorzen)
{
    double *wyniki = new double[ilePowtorzen];

    for(int i = 0; i < ilePowtorzen; i++)
    {
      //  generujKomiwojazer(rozmiar);
        //Tworzenie nowej instancji danych
         Komiwojazer a;

        //Pomiar czasu
        clock_t start = clock();
        a.przegladZupelny();
        clock_t stop = clock();
        
        //Obliczanie wyniku
        double wynikCzastkowy = (stop-start)*1000000/CLOCKS_PER_SEC;
        wyniki[i] = wynikCzastkowy;
                
    }

    //Obliczenie sredniego czasu
    double suma = 0;
    for(int i = 0; i < ilePowtorzen; i++)
    {
        suma += wyniki[i];
    }
    delete [] wyniki;

    return suma/ilePowtorzen;
}


double TimeTest::czasKomiwojazerBoundBranch(int rozmiar, int ilePowtorzen)
{
    double *wyniki = new double[ilePowtorzen];

    for(int i = 0; i < ilePowtorzen; i++)
    {
        //generujKomiwojazer(rozmiar);
        //Tworzenie nowej instancji danych
         Komiwojazer a;

        //Pomiar czasu
        clock_t start = clock();
        a.boundBranch();
        clock_t stop = clock();
        
        //Obliczanie wyniku
        double wynikCzastkowy = (stop-start)*1000000/CLOCKS_PER_SEC;
        wyniki[i] = wynikCzastkowy;
                
    }

    //Obliczenie sredniego czasu
    double suma = 0;
    for(int i = 0; i < ilePowtorzen; i++)
    {
        suma += wyniki[i];
    }
    delete [] wyniki;

    return suma/ilePowtorzen;
}

#endif
