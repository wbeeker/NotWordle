#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <unordered_map>

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

bool guessingGame(string answer) {
    int tries = 0;
    transform(answer.begin(), answer.end(), answer.begin(), ::toupper);

    while (tries < 5) {
        cout << "Enter a five letter word: " << endl;
        string guess;
        cin >> guess;
        transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

        if (guess.size() != 5) {
            cout << "Guess must be exactly 5 letters!" << endl;
            continue;
        }
        unordered_map<char, int> freq;
        for (char c : answer) freq[c]++;

        vector<char> result_colors(5, 'g');

        // Green letter pass
        for (int i = 0; i < guess.size(); ++i) {
            if(guess[i] == answer[i]){
                result_colors[i] = 'G';
                freq[answer[i]]--;
            }
        }

        // Yellow letter pass
        for (int i = 0; i < guess.size(); ++i) {
            if (result_colors[i] != 'G') {
                if (freq[guess[i]] > 0) {
                    result_colors[i] = 'Y';
                    freq[guess[i]]--;
                }
            }
        }

        int count = 0;

        //Display results
        for (int i = 0; i < guess.size(); ++i) {
            if (result_colors[i] == 'G') {
                cout << "\033[32m" << guess[i] << "\033[0m";
                count++;
            } else if (result_colors[i] == 'Y') {
                cout << "\033[33m" << guess[i] << "\033[0m";
            } else {
                cout << guess[i];
            }
        }
        cout << endl;

        if (count == 5) {
            cout << "You guessed correctly! Congratulations!" << endl;
            return true;
        }
        tries++;
    }

    return false;
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

    bool success = guessingGame(answerWord);

    if (!success) {
        cout << "Game over! The correct word was: " << answerWord << endl;
    }

    return 0;
}