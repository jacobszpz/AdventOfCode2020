#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>

using namespace ::std;

// set to true for part one
bool countContainers = false;

// Returns names of bags that contain specified bag (because of eventual duplicates)
set<string> bagSearch(string bag, map<string, map<string, int>> rules) {
    set<string> containersNames;

    // Iterate over bag rule list, iterate over contents list of each bag
    for (auto const &rule : rules) {
        for (auto const &content : rule.second) {
            if (content.first == bag) {
                containersNames.insert(rule.first);
                set<string> childSet = bagSearch(rule.first, rules);
                containersNames.insert(childSet.begin(), childSet.end());
            }
        }
    }

    return containersNames;
}

// Returns amount of bags inside specified one
int contentCount(string bag, map<string, map<string, int>> rules) {
    int bagsInside;

    // Iterate over bag rule list, iterate over contents list of each bag
    map<string, int> &bagRules = rules[bag];

    for (auto const &content : bagRules) {
        bagsInside += content.second;
        bagsInside += (contentCount(content.first, rules) * content.second);
    }

    return bagsInside;
}

int Inception(string text_file) {
    const string myBag = "shiny gold";
    string line;
    ifstream input_file(text_file);

    string contsDelim = " bags contain ";
    string bagsDelim = ", ";
    string noBags = "no other bags";
    string contentNameDelim = " bag";

    int sum = 0;

    typedef map<string, int> bagContent;
    typedef map<string, bagContent> bagRules;
    bagRules rules;

    // Load rules into dictionary
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            int containerPos = line.find(contsDelim);
            string bagName = line.substr(0, containerPos);
            string contents = line.substr(containerPos + contsDelim.length());
            contents = contents.substr(0, contents.length() - 1);

            string bag = "";

            if (contents != noBags) {
                int currentPos = 0;
                int colon_pos;

                do {
                    contents = contents.substr(currentPos);
                    colon_pos = contents.find(bagsDelim);

                    if (colon_pos == -1) {
                        colon_pos = contents.length();
                    }

                    bag = contents.substr(0, colon_pos);
                    currentPos = colon_pos + bagsDelim.length();
                    colon_pos = contents.find(bagsDelim);

                    int nameEnd = bag.find(contentNameDelim);
                    string contentName = bag.substr(2, nameEnd - 2);

                    rules[bagName][contentName] = bag[0] - '0';
                } while (currentPos < contents.length());
            }
        }
        input_file.close();
    }

    if (countContainers) {
        return bagSearch(myBag, rules).size();
    } else {
        return contentCount(myBag, rules);
    }

    return 0;
}

int main() {
    // Part One
    countContainers = true;
    cout << "Part One Answer: " << Inception("input") << endl;

    // Part Two
    countContainers = false;
    cout << "Part Two Answer: " << Inception("input") << endl;

    return 0;
}
