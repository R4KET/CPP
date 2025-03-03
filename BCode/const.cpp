#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    const double PI = 3.14159;
    double radius = 10;
    double circumference = 2 * PI * radius;

    const int WIDTH = 2560;
    const int HEIGHT = 1440;

    const double FARADAY = 96485.33212;

    std::cout << circumference << " cm" << std::endl;
    std::cout << std::fixed << std::setprecision(5) << FARADAY;
    return 0;
}