#include <iostream>
#include <vector>

//typedef std::vector<std::pair<std::string, int>> pairlist_t;

typedef std::string text_t;
typedef int number_t;

int main(){

    text_t firstName = "Micha";
    number_t age = 31;
    std::cout << firstName << '\n';
    std::cout << age << '\n';
    return 0;
}