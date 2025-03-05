#include <iostream>
using namespace std;

string concatString(string string1, string string2);

int main(){

    string firstName = "Test";
    string lastName = "Tester";
    string fullName = concatString(firstName, lastName);

    cout << "Hello, " << fullName;

    return 0;
}

string concatString(string string1, string string2){
    return string1 + " " + string2;
}