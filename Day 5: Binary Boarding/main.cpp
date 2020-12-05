#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace ::std;

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
    
    sort(allCodes, allCodes+codeAmount);
    int firstSeat = allCodes[0];
    
    for (int i = 0; i < codeAmount; i++) {
        if (firstSeat + i != allCodes[i]) {
            cout << "Code missing: " << allCodes[i] - 1 << endl;
            break;
        }
    }

    return highestCode;
}

int main() {
    int highest = MonkeyfiedSnakes("input");
    cout << "Highest Code: " << highest << endl;
    return 0;
}
