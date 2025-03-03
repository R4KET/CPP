#include <iostream>

namespace first{
    int x = 1;
}

namespace second{
    int x = 2;
}

int main() {
    int x = 0;
    std::cout << first::x << std::endl << x << std::endl << second::x;
    return 0;
}