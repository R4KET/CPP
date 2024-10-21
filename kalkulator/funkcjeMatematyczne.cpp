// funkcjeMatematyczne.cpp
#include <iostream>
#include "funkcjeMatematyczne.h"
#include <cmath>

using namespace std;

double dodaj(double A, double B) {
    return A + B;
}

double odejmij(double A, double B) {
    return A - B;
}

double mnoz(double A, double B) {
    return A * B;
}

double dziel(double A, double B) {
    if (B == 0) {
        cout << "Nie mozna dzielic przez zero!" << endl;
        return 0;
    }
    return A / B;
}

double potegowanie(double A, double B) {
    return pow(A, B);
}

double pierwiastkowanie(double A) {
    if (A < 0) {
        cout << "Nie mozna obliczyc pierwiastka z liczby ujemnej!" << endl;
        return -1;
    } else
    return sqrt(A);
}

int modulo(int A, int B) {
    if (B == 0) {
        cout << "Nie mozna dzielic przez zero!" << endl;
        return 0;
    }
    return A % B;
}