#include <iostream>
#include "funkcjeMatematyczne.h"
using namespace std;

int main()
{
    double A;
    double B;
    int dzialanie;
    bool petla = true;

    while (petla)
    {
        cout << "Podaj pierwsza liczbe: " << endl;
        cin >> A;
        cout << "Podaj druga liczbe: " << endl;
        cin >> B;
        cout << "Wybierz opcje: " << endl
             << "1 - dodawanie" << endl
             << "2 - odejmowanie" << endl
             << "3 - mnozenie" << endl
             << "4 - dzielenie" << endl
             << "5 - potegowanie" << endl
             << "6 - pierwiastkowanie" << endl
             << "7 - modulo" << endl
             << "0 - zakonczenie dzialania programu" << endl;
        cin >> dzialanie;
        switch (dzialanie)
        {
        case 1:
            cout << "Wynik dodawania to: " << dodaj(A, B) << endl;
            break;
        case 2:
            cout << "Wynik odejmowania to: " << odejmij(A, B) << endl;
            break;
        case 3:
            cout << "Wynik mnozenia to: " << mnoz(A, B) << endl;
            break;
        case 4:
            cout << "Wynik dzielenia to: " << dziel(A, B) << endl;
            break;
        case 5:
            cout << "Wynik potegowania to: " << potegowanie(A, B) << endl;
            break;
        case 6:
            cout << "Wynik pierwiastkowania to: " << pierwiastkowanie(A) << endl;
            break;
        case 7:
            cout << "Wynik modulo to: " << modulo(static_cast<int>(A), static_cast<int>(B)) << endl;
            break;
        case 0:
            petla = false;
            break;

        default:
            cout << "Niepoprawny wybor. Sprobuj ponownie." << endl;
            break;
        }
    }

    return 0;
}