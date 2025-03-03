#include <iostream>
using namespace std;

int main(){
    string name;
    int age;
    cout << "Whats your name? : ";
    getline(cin, name);
    cout << "What's your age? : ";
    cin >> age;
    cout << "Hello " << name << endl;
    cout << "You are " << age << " years old";
    return 0;
}