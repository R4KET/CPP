#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int students = 20;
    students = students + 1;
    students -= 2;
    cout << "Liczba studentow: " << students << endl;
    int grupa = students % 3;
    int grupa2 = students / 3;
    cout << "Liczba grup mniejszych niz 3 osoby: " << grupa << endl;
    cout << "Liczba grup 3 osobowych: " << grupa2 << endl;
    cout << "Suma studentow: " << 3 * grupa2 + grupa << endl;
    int correct = 8;
    int questions = 10;
    double score = correct / (double)questions * 100;
    cout << "Wynik: " << score << "%";
    return 0;
}