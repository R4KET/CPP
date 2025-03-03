#include <iostream>
#include <cmath>

using namespace std;

int main(){
    double a;
    double b;
    double c;

    cout << "Podaj dlugosc boku A: " << endl;
    cin >> a;
    cout << "Podaj dlugosc boku B: " << endl;
    cin >> b;
    c = sqrt(pow(a,2) + pow(b,2));
    cout << "Dlugosc przekatnej wynosi: " << c << endl;
    return 0;
}