#include <iostream>
#include <ctime>
using namespace std;

int main()
{

    srand(time(0));
    int randNum = rand() % 5 + 1;

    switch (randNum)
    {
    case 1:
        cout << "You win 5$";
        break;
    case 2:
        cout << "You win 1$";
        break;
    case 3:
        cout << "You win 100$";
        break;
    case 4:
        cout << "You lost";
        break;
    case 5:
        cout << "You win 2$";
        break;
    }

    return 0;
}