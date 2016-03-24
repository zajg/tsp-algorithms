
#include <iostream>
using namespace std;

#include "utworzDane.cpp"
#include "timeTest.cpp"

int main(int argc, char** argv)
{
    TimeTest test;
    
    do
    {
        cout << "Problem komiwojazera: metoda podzialu i ograniczen" << endl;
        cout << "1. Wygeneruj dane" << endl;
        cout << "2. Metoda podzialu i ograniczen" << endl;
        cout << "3. Przeglad zupelny" << endl;
        cout << "4. Wyjscie" << endl;
        cout << "Wybor [1-4]: ";
        int wybor;
        cin >> wybor;

        if(wybor == 1)
        {
            cout << "Dla ilu miast chcesz wygenerowac dane? " << endl;
            unsigned int ile;
            cin >> ile;
            generujKomiwojazer(ile);
            cout << "Wygenerowano dane dla " << ile << " miast" << endl;
        }
        else if(wybor == 2)
        {
            cout << "Czas komiwojazer B&B: " << test.czasKomiwojazerBoundBranch(0,1) << " us" << endl;
        }
        else if(wybor == 3)
        {
            cout << "Czas komiwojazer Zupelny: " << test.czasKomiwojazerZupelny(0,1) << " us" << endl;
        }
        else if(wybor == 4)
        {
            break;
        }
        else
        {
            cout << "Podano bledna wartosc" << endl;
        }

    }while(true);
}
