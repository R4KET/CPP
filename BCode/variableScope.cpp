#include <iostream>
using namespace std;

int myNum = 3;

void printNum(int myNum);

int main()
{
    int myNum = 1;
    printNum(::myNum); //:: dla uzycia zmiennych globalnych, w innym wypadku uzywamy zmiennych wewnatzr funkcji (funkcje nie widza co sie dzieje wewnatrz danej funkcji)
    return 0;
}

void printNum(int myNum)
{
    cout << myNum;
}