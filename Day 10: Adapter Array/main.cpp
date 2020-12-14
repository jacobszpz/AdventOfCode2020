#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>

using namespace ::std;

// set to false for part one
bool countPaths = false;

int getDifferences(set<int> adapterSet) {
    int joltage = 0;

    map<int, int> diffMap;
    diffMap[3]++;

    for (auto &adapter : adapterSet) {
        int diff = adapter - joltage;
        diffMap[diff]++;

        joltage = adapter;
    }

    return diffMap[1] * diffMap[3];
}

long long int getPaths(set<int> adapterSet) {
    const int maxJump = 3;
    adapterSet.insert(0);
    vector<int> adapterVector(adapterSet.begin(), adapterSet.end());

    long long int possiblePaths[adapterSet.size()] = {};
    possiblePaths[0] = 1;

    int i = 0;

    for (auto &adapter : adapterVector) {
        for (int j = 1; (j <= maxJump && (i + j) < adapterVector.size()); ++j) {
            if (adapterVector[i + j] <= (adapter + maxJump)) {
                possiblePaths[i + j] += possiblePaths[i];
            }
        }

        i++;
    }

    return possiblePaths[i - 1];
}

long long int MrElectric(string text_file) {
    string line;
    ifstream input_file(text_file);

    set<int> adapterSet;
    

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            adapterSet.insert(stoi(line));
        }
        
        input_file.close();
    }

    if (countPaths) {
        return getPaths(adapterSet);
    } else {
        return getDifferences(adapterSet);
    }
}

int main() {
    // Part One
    countPaths = false;
    cout << "Part One Answer: " << MrElectric("input") << endl;

    // Part Two
    countPaths = true;
    cout << "Part Two Answer: " << MrElectric("input") << endl;
    return 0;
}
