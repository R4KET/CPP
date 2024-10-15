#include <iostream>
using namespace std;

int getValueFromUser()
{
    cout << "Enter an integer: " << endl;
    int input;
    cin >> input;

    return input;
}

int main(){
    int numA{ getValueFromUser() };
    cout << numA << " doubled is: " << numA * 2 << endl;
    int numB{ getValueFromUser() };
    cout << numB << " tripled is: " << numB * 3 << endl;
    return 0;
}