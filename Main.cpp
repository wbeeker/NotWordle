#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

vector<string> readWordList(string filename) {
    ifstream inputFile(filename);
    if(!inputFile.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return {};
    }

    vector<string> wordList;
    string line;
    while(getline(inputFile, line)) {
        wordList.push_back(line);
    }
    return wordList;
}

void guessingGame(string answer) {
    cout << "Enter a five letter word: " << endl;
    string guess;
    cin >> guess;

    if (guess.size() != 5) {
        cout << "Guess must be exactly 5 letters!" << endl;
        return;
    }

    int count = 0;

    for (int i = 0; i < guess.size(); ++i) {
        char c = tolower(guess[i]);
        if (c == answer[i]) {
            cout << "\033[32m" << c << "\033[0m"; // Green letter
            count += 1;
        } else if (answer.find(c) != string::npos) {
            cout << "\033[33m" << c << "\033[0m"; // Yellow letter
        } else if (answer.find(c) != i) {
            cout << c; // Default letter
        }
    }
    cout << endl;

    if (count == 5) {
        cout << "You guessed correctly! Congratulations!" << endl;
        exit(0);
    }
}


int main() {

    srand(time(0));

    string filename;
    vector<string> wordList;

    bool flag = true;

    cout << "Welcome to the Word Guessing Game!" << endl;

    while (true) {
        cout << "Would you like to enter a filename for your Word List? (Y / N)" << endl;
        char answer;
        cin >> answer;
        answer = toupper(answer);

        if (answer == 'Y') {
            cout << "Please enter filename: " << endl;
            cin >> filename;
        } else if (answer == 'N') {
            filename = "word_list.txt";
        } else {
            cout << "Invalid input. Please enter Y or N." << endl;
            continue;
        }

        wordList = readWordList(filename);
        if (!wordList.empty()) {
            break;
        } else {
            cout << "Failed to load list. Please try again.\n" << endl;
        }
    }
    int ind = rand() % wordList.size();
    string answerWord = wordList[ind];

    for (int i = 0; i < 5; ++i) {
        guessingGame(answerWord);
    }
    cout << "Game over! The correct word was: " << answerWord << endl;
    return 0;
}