#include <iostream>
#include <ctime>
using namespace std;

int main()
{

    srand(time(0));

    const int SIZE = 100;
    int numbers[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        numbers[i] = rand() % 100 + 1;
    }

    for (int number : numbers)
    {
        cout << number << endl;
    }

    return 0;
}