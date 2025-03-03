#include <iostream>
#include <ctime>
using namespace std;

int main()
{

    int num;
    int guess;
    int tries = 0;

    srand(time(NULL));
    num = (rand() % 100) + 1;

    cout << "Number guessing game" << endl;

    do
    {
        cout << "Enter a guess between (1-100): ";
        cin >> guess;
        tries++;

        if (guess > num)
        {
            cout << "Too high!" << endl;
        }
        else if (guess < num)
        {
            cout << "Too low!" << endl;
        }
        else
        {
            cout << "Correct! Number of tries: " << tries;
        }

    } while (guess != num);

    return 0;
}