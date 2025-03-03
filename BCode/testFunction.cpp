#include <iostream>
using namespace std;

void happyBday(int repeats)
{
    for (int i = 0; i < repeats; i++)
    {
        cout << "Happy Bday to you!" << endl;
    }
}

int main()
{
    int repeats;
    cout << "Ile razy spiewamy?: " << endl;
    cin >> repeats;
    happyBday(repeats);
    return 0;
}