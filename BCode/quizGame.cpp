#include <iostream>
using namespace std;

int main()
{

    string questions[] = {"1. What years was C++ created?: ", "2. Who invented C++?: ", "3. What is the predecessor of C++?: ", "4. Is the Earth Flat?:"};
    string options[][4] = {{"A. 1969", "B. 1975", "C. 1985", "D. 1989"}, {"A. Guido van Rossum", "B. Bjarne Stroustrup", "C. John Carmack", "D. Mark Zuckerberg"}, {"A. C", "B. C+", "C. C--", "D. B++"}, {"A. Yes", "B. No", "C. Sometimes", "D. What's Earth?"}};

    char answerKey[] = {'C', 'B', 'A', 'B'};

    int size = sizeof(questions) / sizeof(questions[0]);
    char guess;
    int score = 0;

    for (int i = 0; i < size; i++)
    {
        cout << "**************************" << endl;
        cout << questions[i] << endl;
        cout << "**************************" << endl;

        for (int j = 0; j < sizeof(options[i]) / sizeof(options[i][0]); j++)
        {
            cout << options[i][j] << endl;
        }
        cin >> guess;
        guess = toupper(guess);

        if (guess == answerKey[i])
        {
            cout << "CORRECT!" << endl;
            score++;
        }
        else
        {
            cout << "WRONG!" << endl;
            cout << "Answer: " << answerKey[i] << endl;
        }
    }

    cout << "**************************" << endl;
    cout << "Your score is: " << score << endl;
    cout << "**************************" << endl;
    cout << "# of QUESTIONS: " << size << endl;
    cout << "**************************" << endl;
    
    double percentage = (score/(double)size) * 100;

    cout << "SCORE: " << percentage << "%";

    return 0;
}