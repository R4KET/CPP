﻿/*********************************************
Kod stanowi uzupe3nienie materia3ow do aewiczen
w ramach przedmiotu metody optymalizacji.
Kod udostepniony na licencji CC BY-SA 3.0
Autor: dr in?. GBPukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia Gorniczo-Hutnicza
*********************************************/

#include "opt_alg.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void lab1();
void lab2();
void lab3();
// void lab4();
// void lab5();
// void lab6();

int main()
{
	try
	{
		lab3();
		// lab2();
		// lab3();
	}
	catch (string EX_INFO)
	{
		cerr << "ERROR:\n";
		cerr << EX_INFO << endl;
	}
	system("pause");
	return 0;
}

void lab1()
{
	double x0 = m2d(200 * rand_mat() - 100), d = 1, alpha = 5, epsilon = 1e-5, gamma = 1e-200;
	solution opt;
	int Nmax = 1000;

	////Funkcja testowa
	double *ab;
	cout << x0 << endl
		 << endl;
	ab = expansion(ff1T, x0, d, alpha, Nmax);
	cout << ab[0] << '\t' << ab[1] << endl
		 << endl;
	double a = -100;
	double b = 100;
	solution::clear_calls();
	opt = fib(ff1T, ab[0], ab[1], epsilon);
	opt = fib(ff1T, a, b, epsilon);
	cout << opt << endl
		 << endl;
	solution::clear_calls();
	opt = lag(ff1T, ab[0], ab[1], epsilon, gamma, Nmax);
	opt = lag(ff1T, a, b, epsilon, gamma, Nmax);
	cout << opt << endl;
	solution::clear_calls();

	// Zbiorniki
	epsilon = 1e-10;
	opt = fib(ff1R, 1e-4, 1e-2, epsilon);
	int n = get_len(pom[0]);
	for (int i = 0; i < n; ++i)
		cout << pom[0](i, 0) << "," << pom[1](i, 0) << "," << pom[1](i, 1) << "," << pom[1](i, 2) << endl;
	cout << opt << endl
		 << endl;
	solution::clear_calls();
	opt = lag(ff1R, 1e-4, 1e-2, epsilon, gamma, Nmax);
	n = get_len(pom[0]);
	for (int i = 0; i < n; ++i)
		cout << pom[0](i, 0) << "," << pom[1](i, 0) << "," << pom[1](i, 1) << "," << pom[1](i, 2) << endl;
	cout << opt << endl
		 << endl;
	solution::clear_calls();
}

void lab2()
{
	// Funkcja testowa
	double s = 0.7, alphaHJ = 0.5, alphaR = 2, beta = 0.5, epsilon = 1e-3;
	int Nmax = 1000;
	solution opt;
	matrix x0, s0;

	// s0 = matrix(2, 1, s);
	// x0 = 2 * rand_mat(2, 1) - 1;
	////x0(1) = 0.5;
	////x0(0) = 0.5;
	// cout << x0 << endl << endl;
	// opt = HJ(ff2T, x0, s, alphaHJ, epsilon, Nmax);
	// cout << opt << endl << endl;
	// solution::clear_calls();
	// opt = Rosen(ff2T, x0, s0, alphaR, beta, epsilon, Nmax);
	// cout << opt << endl << endl;
	// solution::clear_calls();

	// Ramie robota
	s = 2;

	x0 = 10 * rand_mat(2, 1);
	cout << x0 << endl
		 << endl;
	opt = HJ(ff2R, x0, s, alphaHJ, epsilon, Nmax);
	/*int n = get_len(pom[0]);
	for (int i = 0; i < n; ++i)
		cout << pom[1](i, 0) << "," << pom[1](i, 1) << endl;*/
	cout << opt << endl
		 << endl;
	solution::clear_calls();
	s0 = matrix(2, 1, s);
	opt = Rosen(ff2R, x0, s0, alphaR, beta, epsilon, Nmax);
	/*n = get_len(pom[0]);
	for (int i = 0; i < n; ++i)
		cout << pom[1](i, 0) << "," << pom[1](i, 1) << endl;*/
	cout << opt << endl
		 << endl;
	solution::clear_calls();
}

void lab3()
{
	const double a = 4.0; // Stala wartosc dla parametru 'a'
	const double epsilon = 1e-4;
	const int Nmax = 10000;
	matrix x0;
	std::ofstream outfile("wyniki.csv"); // Tworzenie pliku do zapisu

	// Naglowki dla pliku CSV
	outfile << "Lp,Parametr a,x1(0),x2(0),Zewnetrzna x1*,Zewnetrzna x2*,Zewnetrzna Liczba wywolan,Wewnetrzna x1*,Wewnetrzna x2*,Wewnetrzna Liczba wywolan\n";

	for (int i = 0; i < 100; ++i)
	{
		do
		{
			x0 = 5 * rand_mat(2, 1) + 1;
		} while (norm(x0) > a);

		double c_ex = 1, dc_ex = 2;
		double c_in = 10, dc_in = 0.5;

		// Optymalizacja z zewnetrzna funkcja kary
		solution::clear_calls();
		solution opt_ex = pen(ff3Ta, x0, c_ex, dc_ex, epsilon, Nmax, a);
		int calls_ex = solution::f_calls;

		// Optymalizacja z wewnetrzna funkcja kary
		solution::clear_calls();
		solution opt_in = pen(ff3Tb, x0, c_in, dc_in, epsilon, Nmax, a);
		int calls_in = solution::f_calls;

		// Zapisywanie wynikow do pliku CSV
		outfile << (i + 1) << "," << a << "," << x0(0) << "," << x0(1) << ",";
		outfile << opt_ex.x(0) << "," << opt_ex.x(1) << "," << calls_ex << ",";
		outfile << opt_in.x(0) << "," << opt_in.x(1) << "," << calls_in << "\n";
	}

	outfile.close(); // Zamknięcie pliku
}
// Rzut pilka
/*
x0 = matrix(2, 1);
x0(0) = 20 * m2d(rand_mat()) - 10;
x0(1) = 40 * m2d(rand_mat()) - 20;
cout << x0 << endl << endl;
opt = pen(ff3R, x0, c_ex, dc_ex, epsilon, Nmax);
int n = get_len(pom[0]);
for (int i = 0; i < n; ++i)
	cout << pom[1](i, 0) << "," << pom[1](i, 2) << endl;
opt.y = -opt.y;
cout << opt << endl;
solution::clear_calls();
*/