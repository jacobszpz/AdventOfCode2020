#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace ::std;

// set to true for part one
bool gMaskValue = false;

struct Instruction;
int findAddress(string instr);
unsigned long long int getAndMask(string mask, bool inverse);
unsigned long long int getOrMask(string mask);
vector<string> getOutcomes(string input, char replace);
map<unsigned long long, unsigned long long> maskValue(vector<Instruction> seq);
map<unsigned long long, unsigned long long> maskAddress(vector<Instruction> seq);
unsigned long long int TheMask(string text_file);

enum InstructionType {
    New_Mask,
    Write_Mem
};

struct Instruction {
    InstructionType type;
    string newValue;
    unsigned long long int address;
    const char valueDelim;

    Instruction(string line): valueDelim('=') {
        string t = line.substr(0, 3);

        if (t == "mem") {
            type = Write_Mem;
            address = findAddress(line);
        } else {
            type = New_Mask;
        }

        int valuePos = line.find(valueDelim);
        newValue = line.substr(valuePos + 2);

    }
};

unsigned long long int getAndMask(string mask, bool inverse = false) {
    unsigned long long int newMask = 1;

    for (int i = 0; i < mask.length(); ++i) {
        newMask <<= 1;
        newMask += ((mask[i] == 'X') != inverse);
    }

    return newMask;
}

unsigned long long int getOrMask(string mask) {
    unsigned long long newMask = 0;

    for (int i = 0; i < mask.length(); ++i) {
        newMask <<= 1;       
        newMask += (mask[i] == '1');
    }

    return newMask;
}

string preserveOnlyX(string mask) {
    string newMask(mask.length(), '0');
    for (int i = 0; i < mask.length(); ++i) {
        if (mask[i] == 'X') {
            newMask[i] = 'X';
        }
    }

    return newMask;
}

vector<string> getOutcomes(string input, char replace = '0') {
    vector<string> outcomes;
    string base = "";

    int pos = 0;
    bool replaced = false || (replace == 'X');
    int options[] = {'0', '1'};

    for (; pos < input.length(); ++pos) {
        char next = input[pos];

        if (next != 'X') {
            base += next;
        } else {
            if (!replaced) {
                base += replace;
                replaced = true;
            } else {
                for (int i = 0; i <= 1; ++i) {
                    vector<string> branch = getOutcomes(input.substr(pos), options[i]);
                    outcomes.insert(outcomes.end(), branch.begin(), branch.end());
                }

                break;
            }
        }
    }

    if (!outcomes.size()) {
        outcomes.push_back(base);
    } else {
        for (auto &outcome : outcomes) {
            outcome = base + outcome;
        }
    }

    return outcomes;
}

map<unsigned long long, unsigned long long> maskValue(vector<Instruction> seq) {
    map<unsigned long long, unsigned long long> mem;
    unsigned long long andMask, orMask;

    for (Instruction &ins: seq) {
        unsigned long long write;

        if (ins.type == Write_Mem) {
            write = ((stoi(ins.newValue) & andMask) | orMask);
            mem[ins.address] = write;
        } else {
            andMask = getAndMask(ins.newValue);
            orMask = getOrMask(ins.newValue);
        }
    }

    return mem;
}

map<unsigned long long, unsigned long long> maskAddress(vector<Instruction> seq) {
    map<unsigned long long, unsigned long long> mem;
    vector<unsigned long long> allMasks;
    unsigned long long andMask, orMask;

    for (Instruction &ins: seq) {
        vector<unsigned long long> addresses;
        unsigned long long write, preMasked;        

        if (ins.type == Write_Mem) {
            write = stoi(ins.newValue);
            preMasked = ((ins.address | orMask) & andMask);

            for (auto &mask : allMasks) {
                mem[(preMasked | mask)] = write;
            }
            
        } else {
            allMasks.clear();
            orMask = getOrMask(ins.newValue);
            andMask = getAndMask(ins.newValue, true);
            string xMask = preserveOnlyX(ins.newValue);

            for (auto &outcome : getOutcomes(xMask, 'X')) {
                allMasks.push_back(getOrMask(outcome));
            }
        }
    }

    return mem;
}

int findAddress(string instr) {
    const char addrStartD = '[';
    const char addrEndD = ']';
    int addrStart, addrEnd;
    int address;

    addrStart = instr.find(addrStartD) + 1;
    addrEnd = instr.find(addrEndD) - addrStart;
    address = stoi(instr.substr(addrStart, addrEnd));

    return address;
}


unsigned long long int TheMask(string text_file) {
    string line;
    ifstream input_file(text_file);

    unsigned long long int sum = 0;
    map<unsigned long long int, unsigned long long int> mem;

    vector<Instruction> seq;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            seq.push_back(Instruction(line));
        }
        
        input_file.close();
    }

    if (gMaskValue) {
        mem = maskValue(seq);
    } else {
        mem = maskAddress(seq);
    }

    for (auto &location : mem) {
        sum += location.second;
    }
    
    return sum;
}


int main() {
    // Part One
    gMaskValue = true;
    cout << "Part One Answer: " << TheMask("input") << endl;

    // Part Two
    gMaskValue = false;
    cout << "Part Two Answer: " << TheMask("input") << endl;
    return 0;
}
