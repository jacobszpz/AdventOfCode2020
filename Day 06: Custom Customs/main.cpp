#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>

using namespace ::std;

// set to true for part one
bool anyone = true;

int Hamburger(string text_file) {
    string line;
    ifstream input_file(text_file);

    string group = "";
    vector<string> vGroup = {};

    int sum = 0;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            if (line == "") {
                if (anyone) {
                    set<char> questions(group.begin(), group.end());
                    sum += questions.size();
                    group = "";

                } else {
                    for (int i = 0; i < vGroup.size(); i++) {
                        sort(vGroup[i].begin(), vGroup[i].end()); 
                    }

                    vector<char> lastIntersection(vGroup[0].begin(), vGroup[0].end());
                    vector<char> currentIntersection;

                    for (int i = 1; i < vGroup.size(); i++) {
                        set_intersection(lastIntersection.begin(), lastIntersection.end(),
                                         vGroup[i].begin(), vGroup[i].end(),
                                         back_inserter(currentIntersection));
                        swap(lastIntersection, currentIntersection);
                        currentIntersection.clear();
                    }

                    sum += lastIntersection.size();
                    vGroup = {};
                }
            } else {
                if (anyone) {
                    group.append(line);
                } else {
                    vGroup.push_back(line);
                }
            }
        }
        input_file.close();
    }

    return sum;
}

int main() {
    anyone = true;
    cout << "Part One Answer: " << Hamburger("input") << endl;

    anyone = false;
    cout << "Part Two Answer: " << Hamburger("input") << endl;

    return 0;
}
