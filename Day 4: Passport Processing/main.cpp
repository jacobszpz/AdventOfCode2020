#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace ::std;

// Perhaps using C++ wasn't the best idea after all
// Add a line at the end of your input file if not using the one included along this solution

bool validNo(string value, int min, int max) {
    int year = stoi(value);
    if (year < min || year > max) {
        return false;
    }
    
    return true;
}

bool passValid(string passport) {
    string fields[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};
    
    bool bValid = true;
    bool bHasRequiredAttributes = false;
    bool cid = false;
    
    // Change to true for part 2
    const bool validateValues = false;
    
    cout << "Passport " << passport << ", ";
    
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
        
        if (attr_name == "cid") {
            cid = true;
        }
        
        if (validateValues) {
            if (attr_name == "byr") {
                bValid = bValid && validNo(attr_value, 1920, 2002);
            } else if (attr_name == "iyr") {
                bValid = bValid && validNo(attr_value, 2010, 2020);
            } else if (attr_name == "eyr") {
                bValid = bValid && validNo(attr_value, 2020, 2030);
            } else if (attr_name == "hgt") {
                string measure = attr_value.substr(attr_value.length() - 2);
                if (measure == "cm") {
                    bValid = bValid && validNo(attr_value, 150, 193);
                } else if (measure == "in") {
                    bValid = bValid && validNo(attr_value, 59, 76);
                } else {
                    bValid = false;
                }
            } else if (attr_name == "hcl") {
                if (attr_value[0] == '#' && attr_value.length() == 7) {
                    bValid = bValid && all_of(attr_value.begin() + 1, attr_value.end(), ::isalnum);
                } else {
                    bValid = false;
                }
                
            } else if (attr_name == "ecl") {
                // Don't know how to simplify this yet, sorry
                if (attr_value != "amb" && attr_value != "blu" && attr_value != "brn" && attr_value != "gry" && attr_value != "grn" && attr_value != "hzl" && attr_value != "oth") {
                    bValid = false;
                }
                
            } else if (attr_name == "pid") {
                if (attr_value.length() == 9) {
                    bValid = bValid && all_of(attr_value.begin(), attr_value.end(), ::isdigit);
                } else {
                    bValid = false;
                }
            }
        }
    }
    
    cout << bValid << endl;
    bHasRequiredAttributes = (attrCount == 8 || ((attrCount == 7) && !cid));
    return bHasRequiredAttributes && bValid;
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
    cout << Multipass("input") << endl;
    return 0;
}
