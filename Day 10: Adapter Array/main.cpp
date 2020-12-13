#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace ::std;

// set to true for part one
bool countLetter = false;

int MrElectric(string text_file) {
    string line;
    ifstream input_file(text_file);

    set<int> adapterSet;
    int joltage = 0;

    map<int, int> diffMap;
    diffMap[3]++;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            adapterSet.insert(stoi(line));
        }
        
        input_file.close();
    }

    for (auto &adapter : adapterSet) {
        int diff = adapter - joltage;
        diffMap[diff]++;

        joltage = adapter;
    }

    return diffMap[1] * diffMap[3];
}

int main() {
    // Part One
    //countLetter = true;
    cout << "Part One Answer: " << MrElectric("input") << endl;

    // Part Two
    /*countLetter = false;
    cout << "Part Two Answer: " << PassPolicy("input") << endl;*/
    return 0;
}
