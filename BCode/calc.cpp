#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double a;
    double b;
    double c;
    int opcja;
    cout << "Podaj liczbe A: " << endl;
    cin >> a;
    cout << "Podaj liczbe B: " << endl;
    cin >> b;
    cout << "Co chcesz zrobic? (1 - dodawanie, 2 - odejmowanie, 3 - mnozenie, 4 - dzielenie): " << endl;
    cin >> opcja;

    switch (opcja)
    {
    case 1:
        c = a + b;
        break;
    case 2:
        c = a - b;
        break;
    case 3:
        c = a * b;
        break;
    case 4:
        c = a / b;
        break;

    default:
        cout << "Wybierz opcje od 1 do 4!";
        break;
    }

    cout << c;
    return 0;
}