#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace ::std;
int gTurns = 0;

long int Elf(string input) {
    const char startDelim = ',';
    int currentPos = 0, commaPos;
    vector<int> starting;
    map<long int, long int> history;

    do {
        input = input.substr(currentPos);
        commaPos = input.find(startDelim);

        if (commaPos == -1) {
            commaPos = input.length();
        }

        starting.push_back(stoi(input.substr(0, commaPos)));
        currentPos = commaPos + 1;
    } while (currentPos < input.length());

    long int turn = 0;
    int lastSpoken = 0, newSpoken = 0;

    while (turn != gTurns) {
        if (turn < starting.size()) {
            newSpoken = starting[turn];
        } else {
            if (history.count(lastSpoken)) {
                newSpoken = (turn - 1) - (history[lastSpoken]);
            } else {
                newSpoken = 0;
            }
        }

        if (turn > 0) {
            history[lastSpoken] = turn - 1;
        }

        lastSpoken = newSpoken;
        turn++;
    }

    return lastSpoken;
}

int main() {
    string test = "0,3,6";
    string input = "20,0,1,11,6,3";

    // Part One
    gTurns = 2020;
    cout << "Part One Answer: " << Elf(input) << endl;

    cout << "This can take a while (< 2m), sit tight" << endl;

    // Part Two
    gTurns = 30000000;
    cout << "Part Two Answer: " << Elf(input) << endl;
    return 0;
}
