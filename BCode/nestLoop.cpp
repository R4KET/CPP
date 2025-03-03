#include <iostream>
using namespace std;

int main()
{
    int rows;
    int columns;
    char symbol;

    cout << "How many rows?: ";
    cin >> rows;
    cout << "How many columns?: ";
    cin >> columns;
    cout << "Enter a symbol to use: ";
    cin >> symbol;

    for (int i = 0; i <= rows; i++)
    {
        for (int j = 0; j <= columns; j++)
        {
            cout << symbol << ' ';
        }
        cout << '\n';
    }

    return 0;
}