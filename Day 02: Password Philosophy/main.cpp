#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

using namespace ::std;

// set to true for part one
bool countLetter = false;

bool isValid(string line) {
    bool valid;

    int colon_pos = line.find(':');
    int dash_pos = line.find('-');

    string password = line.substr(colon_pos + 2, line.length());
    char letter = line[colon_pos - 1];
    
    int start_pos = stoi(line.substr(0, dash_pos));
    int end_pos = stoi(line.substr(dash_pos + 1, colon_pos));            
    
    if (countLetter) {
        int letterCount = count(password.begin(), password.end(), letter);
        valid = (letterCount >= start_pos && letterCount <= end_pos);
    } else {
        bool start_valid = (char) password[start_pos - 1] == letter;
        bool end_valid = (char) password[end_pos - 1] == letter;
        valid = (start_valid != end_valid);
    }

    return valid;
}

int PassPolicy(string text_file) {
    string line;
    ifstream input_file(text_file);

    int valid_pass = 0;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            if (isValid(line)) {
                valid_pass++;
            }
        }
        
        input_file.close();
    }
    
    return valid_pass;
}

int main() {
    // Part One
    countLetter = true;
    cout << "Part One Answer: " << PassPolicy("input") << endl;

    // Part Two
    countLetter = false;
    cout << "Part Two Answer: " << PassPolicy("input") << endl;
    return 0;
}
