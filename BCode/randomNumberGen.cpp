#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    int diceSize;
    int rolls;
    cout << "Podaj typ kosci: ";
    cin >> diceSize;
    cout << "Podaj ilosc rzutow: ";
    cin >> rolls;
    int sumRolls = 0;

    srand(time(NULL));
    for (int i = 0; i < rolls; i++)
    {
        int dice = (rand() % diceSize) + 1;
        cout << "Kosc " << i+1 << " : " << dice << endl;
        sumRolls += dice;
    }
    cout << "Suma rzutow: " << sumRolls;

    return 0;
}