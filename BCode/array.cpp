#include <iostream>
using namespace std;

int main()
{

    string cars[3];

    cars[0] = "Camaro";
    cars[1] = "Mustang";
    cars[2] = "Camry";

    for (int i = 0; i < 3; i++)
    {
        cout << cars[i] << " ";
    }

    cout << "----" << endl;

    double prices[] = {5.00, 7.50, 9.99, 15.00};

    for (int i = 0; i < 4; i++)
    {
        cout << prices[i] << " ";
    }

    cout << "----" << endl;
    char letters[] = {'A', 'B', 'C', 'D', 'E'};

    for (int i = 0; i < sizeof(letters) / sizeof(char); i++)
    {
        cout << letters[i] << " ";
    }
    
    cout << "----" << endl;
    return 0;
}
