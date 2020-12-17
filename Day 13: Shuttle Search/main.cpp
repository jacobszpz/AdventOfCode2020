#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace ::std;

// set to true for part one
bool gUseTimestamp = false;

struct Bus {
    int r;
    int id;

    Bus(int p, int id) : r(p), id(id) {}
};

long long int StayAbove50(string text_file) {
    string line;
    ifstream input_file(text_file);

    int timestamp;
    char busDelim = ',';
    vector<Bus> buses;

    // Load file to memory
    if (input_file.is_open()) {
        getline(input_file, line);
        timestamp = stoi(line);

        getline(input_file, line);
        string schedule = line;

        string bus;
        int currentPos = 0, commaPos, currentBus = 0;

        do {
            schedule = schedule.substr(currentPos);
            commaPos = schedule.find(busDelim);

            if (commaPos == -1) {
                commaPos = schedule.length();
            }

            bus = schedule.substr(0, commaPos);

            if (bus != "x") {
                buses.push_back(Bus(currentBus, stoi(bus)));
            }
            currentPos = commaPos + 1;
            currentBus++;
        } while (currentPos < schedule.length());

        input_file.close();
    }

    if (gUseTimestamp) {
        int highestR = 0, earliestBus;
        for (Bus &bus : buses) {
            int r = (timestamp % bus.id);
            highestR = max(r, highestR);

            if (r == highestR) {
                earliestBus = bus.id;
            }
        }

        return (earliestBus - highestR) * earliestBus;

    } else {
        
    }
    
    return 0;
}

int main() {
    // Part One
    gUseTimestamp = true;
    cout << "Part One Answer: " << StayAbove50("input") << endl;

    // Part Two
    gUseTimestamp = false;
    //StayAbove50("test");
    //cout << "Part Two Answer: " <<  << endl;
    return 0;
}
