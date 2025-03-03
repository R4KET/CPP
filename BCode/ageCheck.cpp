#include <iostream>
using namespace std;

int main()
{
    int age;

    cout << "Enter yours age: ";
    cin >> age;
    if (age < 18)
    {
        cout << "You cannot enter this site!";
    }
    else if (age < 0 || age > 120)
    {
        cout << "You are dead!";
    }
    else
    {
        cout << "Welcome!";
    }
    return 0;
}
