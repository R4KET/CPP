#include <iostream>
using namespace std;

int main()
{

    string students[] = {"Patrick", "Mark", "Jake", "John"};

    for(string student : students){
        cout << student << "\n";
    }

    return 0;
}
