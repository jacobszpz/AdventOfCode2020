#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace ::std;

// Set to true for part one
bool highest = true;

int parseCode(string input, char lowerHalf = 'B') {
    double power = 2;
    int row = 0;
    int range = pow(power, input.length());
    
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == lowerHalf) {
            row += (range / 2);
        }
        
        range /= power;
    }
        
    return row;
}

int MonkeyfiedSnakes(string text_file) {
    string line;
    ifstream input_file(text_file);
    
    // Number of lines in file
    int codeAmount = 927;
    
    int highestCode = 0;
    int allCodes[codeAmount] = {};
    int i = 0;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            int row = parseCode(line.substr(0, 7));
            int col = parseCode(line.substr(7), 'R');
            int code = row * 8 + col;
            
            highestCode = max(code, highestCode);
            allCodes[i] = code;
        
            i++;
        }
        input_file.close();
    }

    if (highest) {
        return highestCode;
    }
    
    sort(allCodes, allCodes+codeAmount);
    int firstSeat = allCodes[0];
    
    for (int i = 0; i < codeAmount; i++) {
        if (firstSeat + i != allCodes[i]) {
            return allCodes[i] - 1;
        }
    }

    return 0;
}

int main() {
    highest = true;
    cout << "Part One Answer: " << MonkeyfiedSnakes("input") << endl;

    highest = false;
    cout << "Part Two Answer: " << MonkeyfiedSnakes("input") << endl;
    return 0;
}
