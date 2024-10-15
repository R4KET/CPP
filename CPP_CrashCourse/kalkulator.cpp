#include <iostream>
using namespace std;



int add(int x, int y){
    return x + y;
}
int substract(int x, int y){
    return x - y;
}
int multiply(int x, int y){
    return x * y;
}
float divide(int x, int y){
    if (y != 0) {
        return static_cast<float>(x) / y; // casting x to float
    } else {
        cout << "Error: Division by zero!" << endl;
        return 0; // return 0 or handle this case differently
    }
}

int main(){
    int x,y;
    cout << "Enter an integer: " << endl;
    cin >> x;
    cout << "Enter another integer: " << endl;
    cin >> y;
    cout << "Sum: " << add(x, y) << endl;
    cout << "Difference: " << substract(x, y) << endl;
    cout << "Product: " << multiply(x, y) << endl;
    cout << "Quotient: " << divide(x, y) << endl;
    return 0;
}