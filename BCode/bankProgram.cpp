#include <iostream>
#include <iomanip>
using namespace std;

void showBalance(double balance);
double deposit();
double withdraw(double balance);

int main()
{
    double balance = 1000;
    int choice = 0;

    do
    {
        cout << "Enter your choice: \n";
        cout << "1. Show balance\n";
        cout << "2. Deposit money\n";
        cout << "3. Withdraw money\n";
        cout << "4. Exit\n";

        cin >> choice;

        switch (choice)
        {
        case 1:
            showBalance(balance);
            break;
        case 2:
            balance = balance + deposit();
            showBalance(balance);
            break;
        case 3:
            balance = balance - withdraw(balance);
            showBalance(balance);
            break;
        case 4:
            cout << "Thanks for visiting!";
            break;

        default:
            cout << "Use option 1-4!\n";
            break;
        }

    } while (choice != 4);
    {
        /* code */
    }

    return 0;
}

void showBalance(double balance)
{
    cout << "My balance is: " << setprecision(2) << fixed << balance << "$\n";
}

double deposit()
{

    double amount = 0;
    cout << "Enter the amount to deposit: ";
    cin >> amount;
    if(amount > 0) {
        return amount;
    } else {
        cout << "That's not a valid amount!\n";
        return 0;
    }
}

double withdraw(double balance)
{   
    double amount = 0;
    cout << "Enter the amount to withdraw: ";
    cin >> amount;
    if(amount > balance) {
        cout <<"You dont have enough money to withdraw!\n";
        return 0;
    } else {
        return amount;
    }
    return amount;
}