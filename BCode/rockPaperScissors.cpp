#include <iostream>
#include <ctime>
using namespace std;

char getUserChoice();
char getComputerChoice();
void showChoice(char choice);
void chooseWinner(char player, char computer);

int main()
{

    char player;
    char computer;

    player = getUserChoice();
    cout << "You choice: ";
    showChoice(player);
    cout << endl;

    computer = getComputerChoice();
    cout << "Computer choice: ";
    showChoice(computer);
    cout << endl;

    chooseWinner(player, computer);

    return 0;
}

char getUserChoice()
{
    char player;

    do
    {
        cout << "Rock Paper Scissor Game!\n";
        cout << "r - for rock\n";
        cout << "p - for paper\n";
        cout << "s - for scissors\n";
        cin >> player;
    } while (player != 'r' && player != 'p' && player != 's');

    return player;
}
char getComputerChoice()
{
    srand(time(0));
    int num = rand() % 3 + 1;

    switch (num)
    {
    case 1:
        return 'r';
    case 2:
        return 's';
    case 3:
        return 'p';
    }

    return 0;
}
void showChoice(char choice)
{
    switch (choice)
    {
    case 'r':
        cout << "Rock!";
        break;
    case 's':
        cout << "Scissors!";
        break;
    case 'p':
        cout << "Paper!";
        break;

    default:
        break;
    }
}
void chooseWinner(char player, char computer)
{
    if ((player == 'r' && computer == 'r') || (player == 's' && computer == 's') || (player == 'p' && computer == 'p'))
    {
        cout << "DRAW";
    }
    else if ((player == 'r' && computer == 's') || (player == 's' && computer == 'p') || (player == 'p' && computer == 'r'))
    {
        cout << "PLAYER WON!";
    }
    else
    {
        cout << "COMPUTER WON!";
    }
}