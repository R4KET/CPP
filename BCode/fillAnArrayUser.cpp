#include <iostream>
using namespace std;

int main()
{
    const int SIZE = 99;
    string foods[SIZE];

    fill(foods, foods + (SIZE / 3), "pizza");
    fill(foods + (SIZE / 3), foods + (SIZE / 3) * 2, "burgers");
    fill(foods + (SIZE / 3) * 2, foods + SIZE, "hot dogs");

    for (string food : foods)
    {
        cout << food << endl;
    }

    return 0;
}