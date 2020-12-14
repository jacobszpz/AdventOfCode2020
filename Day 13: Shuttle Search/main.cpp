#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace ::std;

int StayAbove50(string text_file) {
    string line;
    ifstream input_file(text_file);

    int timestamp;
    char busDelim = ',';
    vector<int> buses;

    // Load file to memory
    if (input_file.is_open()) {
        getline(input_file, line);
        timestamp = stoi(line);

        getline(input_file, line);
        string schedule = line;

        string bus;
        int currentPos = 0, commaPos;

        do {
            schedule = schedule.substr(currentPos);
            commaPos = schedule.find(busDelim);

            if (commaPos == -1) {
                commaPos = schedule.length();
            }

            bus = schedule.substr(0, commaPos);

            if (bus != "x") {
                buses.push_back(stoi(bus));
            }
            currentPos = commaPos + 1;
        } while (currentPos < schedule.length());

        input_file.close();
    }

    int currentTime = timestamp;
    while (true) {
        for (auto &bus : buses) {
            if (currentTime % bus == 0) {
                return (currentTime - timestamp) * bus;
            }
        }
        
        currentTime++;
    }
    
    return 0;
}

int main() {
    // Part One
    cout << "Part One Answer: " << StayAbove50("input") << endl;
/*
    // Part Two
    countLetter = false;
    cout << "Part Two Answer: " << PassPolicy("input") << endl;*/
    return 0;
}
