// pobieranieLiczb.cpp
#include <iostream>
using namespace std;

double pobierzLiczbeOdUzytkownika()
{
    double liczba;

    while (true)
    {
        cout << "Podaj liczbe: " << endl;
        cin >> liczba;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Niepoprawna wartosc. Sproboj ponownie." << endl;
        }
        else
        {
            break;
        }
    }

    return liczba;
}