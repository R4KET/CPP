#include <iostream>
using namespace std;

int main()
{
    for (int i = 0; i <= 20; i++)
    {
        if (i == 13)
        {
            continue; //Continue skipuje dana iteracje, a przy brake konczymy na niej (a wlasciwie przed nia, 12)
        }

        cout << i << endl;
    }

    return 0;
}