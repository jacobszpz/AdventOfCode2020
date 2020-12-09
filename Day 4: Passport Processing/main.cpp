#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace ::std;

// Set to true for part two
bool validateValues = false;

// Perhaps using C++ wasn't the best idea after all
// Add an extra line at the end of your input file if not using the one included along this solution

bool validNo(string value, int min, int max) {
    int year = stoi(value);
    if (year < min || year > max) {
        return false;
    }

    return true;
}

bool passValid(string passport) {
    string fields[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
    string eyeColours[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

    bool bValidValues = true;
    bool cid = false;

    int attrCount = count(passport.begin(), passport.end(), ' ');

    string attr[attrCount] = {};

    int attr_i = -1;

    for (int i = 0; i < passport.length(); i++) {
        if (passport[i] == ' ') {
            attr_i++;
        } else {
            attr[attr_i] = attr[attr_i] + passport[i];
        }
    }

    for (int i = 0; i < attrCount; i++) {
        string attr_name = attr[i].substr(0, 3);
        string attr_value = attr[i].substr(4);

        auto itr = find(fields, end(fields), attr_name);
        int attr_i = distance(fields, itr);

        switch (attr_i) {
            case 0: {
                bValidValues &= validNo(attr_value, 1920, 2002);}
                break;
            case 1: {
                bValidValues &= validNo(attr_value, 2010, 2020);}
                break;
            case 2: {
                bValidValues &= validNo(attr_value, 2020, 2030);}
                break;
            case 3: {
                string measure = attr_value.substr(attr_value.length() - 2);

                if (measure == "cm") {
                    bValidValues &= validNo(attr_value, 150, 193);
                } else if (measure == "in") {
                    bValidValues &= validNo(attr_value, 59, 76);
                } else {
                    bValidValues = false;
                }}

                break;
            case 4: {
                if (attr_value.length() == 7 && attr_value[0] == '#') {
                    bValidValues &= all_of(attr_value.begin() + 1, attr_value.end(), ::isalnum);
                } else {
                    bValidValues = false;
                }}
                break;
            case 5: {
                auto eyeColourItr = find(eyeColours, end(eyeColours), attr_value);
                bValidValues &= (eyeColourItr != end(eyeColours));}
                break;
            case 6: {
                if (attr_value.length() == 9) {
                    bValidValues &= all_of(attr_value.begin(), attr_value.end(), ::isdigit);
                } else {
                    bValidValues = false;
                }}
                break;
            case 7: {
                cid = true;}
                break;
        }
    }

    bool bAllFields = (attrCount == 8 || ((attrCount == 7) && !cid));

    if (!validateValues) {
        return bAllFields;
    }

    return bAllFields && bValidValues;
}

int Multipass(string text_file) {
    string line;
    ifstream input_file(text_file);

    int valid = 0;
    string separator = " ";

    if (input_file.is_open()) {
        string passport;

        while (getline(input_file, line)) {
            if (line == "") {
                if (passValid(passport)) {
                    valid++;
                }
                passport = "";
            } else {
                passport.append(separator + line);
            }
        }

        input_file.close();
    }
    return valid;
}

int main() {
    validateValues = false;
    cout << "Part One Answer: " << Multipass("input") << endl;

    validateValues = true;
    cout << "Part Two Answer: " << Multipass("input") << endl;
    return 0;
}
