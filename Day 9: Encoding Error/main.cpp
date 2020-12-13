#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace ::std;

// set to true for part one
bool onlyInvalid = false;

int findInvalid(vector<long long int> xmas, int preambleSize) {
    int i = 0;
    int preamble[preambleSize];

    for (auto &num : xmas) {
        if (i < preambleSize) {
            preamble[i] = num;
        } else {
            bool valid = false;

            // anyone say bruteforce?
            for (int j = 0; j < preambleSize; j++) {
                for (int k = 0; k < preambleSize; k++) {
                    if (preamble[j] != preamble[k]) {
                        if ((preamble[j] + preamble[k]) == num) {
                            valid = true;
                        }
                    }
                }
            }

            if (!valid) {
                return num;
            }

            // shift array elements
            for (int i = 1; i < preambleSize; i++) {
                preamble[i - 1] = preamble[i];
            }
            preamble[preambleSize - 1] = num;
        }

        i++;
    }

    return -1;
}

vector<long long int> findContiguous(vector<long long int> xmas, int toFind) {
    int i = 0;

    for (auto &num : xmas) {
        vector<long long int> addends;
        int sum = 0;

        for (int j = 0; j <= i; j++) {
            int addend = xmas[i - j];

            sum += addend;
            addends.push_back(addend);

            if (sum == toFind && j > 0) {
                return addends;
            }
        }

        i++;
    }

    return vector<long long int>();
}

int Hackerman(string text_file) {
    int preambleSize = 25;

    string line;
    ifstream input_file(text_file);

    vector<long long int> xmas;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            xmas.push_back(stoll(line));
        }
        
        input_file.close();
    }

    int invalid = findInvalid(xmas, preambleSize);
    
    if (onlyInvalid) {
        return invalid;   
    }

    vector<long long int> addends = findContiguous(xmas, invalid);

    int smallest = addends[0], largest = addends[0];

    for (auto &addend : addends) {
        smallest = (addend < smallest) ? addend : smallest;
        largest = (addend > largest) ? addend : largest;
    }

    return smallest + largest;
}

int main() {
    // Part One
    onlyInvalid = true;
    cout << "Part One Answer: " << Hackerman("input") << endl;

    // Part Two
    onlyInvalid = false;
    cout << "Part Two Answer: " << Hackerman("input") << endl;
    return 0;
}
