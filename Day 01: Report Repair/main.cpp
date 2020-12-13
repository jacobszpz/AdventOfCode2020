#include <string>
#include <iostream>
#include <fstream>

using namespace ::std;

// set to 2 for part one
int minLevel = 3;

// Arrays are by default passed by reference
bool getComplement(int expenses[], int expenseCount, int remainder, int usedExpenses[], int minLevel, int level = 0) {
    for (int i = 0; i < expenseCount; i++) {
        int newRemainder = remainder - expenses[i];
        usedExpenses[level] = expenses[i];

        if (((level + 1) == minLevel) && !newRemainder) {
            return true;
        }  else if (((level + 1) < minLevel) && (newRemainder > 0)) {
            if (getComplement(expenses, expenseCount, newRemainder, usedExpenses, minLevel, level + 1)) {
                return true;
            }
        }
    }

    return false;
}

int MissionReport(string text_file) {
    int remainder = 2020;
    int expenseCount = 200;

    string line;
    ifstream input_file(text_file);
    int expenses[expenseCount] = {};
    
    // Copy file contents to array
    if (input_file.is_open()) {
        int i = 0;

        while (getline(input_file, line)) {
            expenses[i] = stoi(line);
            i++;
        }

        input_file.close();
    }

    int usedExpenses[minLevel] = {};
    getComplement(expenses, expenseCount, remainder, usedExpenses, minLevel);

    string reported = "";
    int product = 1;

    for (int i = 0; i < minLevel; i++) {
        reported += to_string(usedExpenses[i]) + " ";
        product *= usedExpenses[i];
    }

    cout << "Factors: " << reported << endl;

    return product;
}

int main() {
    // Part One
    minLevel = 2;
    int partOne = MissionReport("input");
    cout << "Part One Answer: " << partOne << endl;

    // Part Two
    minLevel = 3;
    int partTwo = MissionReport("input");
    cout << "Part Two Answer: " << partTwo << endl;

    return 0;
}
