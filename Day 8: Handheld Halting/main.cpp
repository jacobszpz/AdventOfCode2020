#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace ::std;

// set to false for part one
bool bruteForce = true;

enum Operation {
    acc,
    jmp,
    nop
};

struct Instruction {
    private:
        Operation operation;
        int value;
        bool run;

        Operation strop(string op) {
            if (op == "acc") {
                return acc;
            } else if (op == "jmp") {
                return jmp;
            } else {
                return nop;
            }
        }

        string opts(Operation op) {
            if (op == acc) {
                return "acc";
            } else if (op == jmp) {
                return "jmp";
            } else {
                return "nop";
            }
        }
    

    public:
        Instruction(string op, int v) {
            operation = strop(op);
            value = v;
            run = false;
        }

        Operation getOperation() {
            return operation;
        }

        string getOperationStr() {
            return opts(operation);
        }

        int getValue() {
            return value;
        }

        bool hasRun() {
            return run;
        }

        void setRun() {
            run = true;
        }

        void switchJmpNop() {
            if (operation == nop) {
                operation = jmp;
            } else if (operation == jmp) {
                operation = nop;
            }
        }
};

int runBootSequence(vector<Instruction> bootSequence, bool onlyComplete=false) {
    int accumulator = 0;
    int bootI = 0;

    while (true) {
        Instruction &ins = bootSequence[bootI];

        if (ins.hasRun()) {
            if (onlyComplete) {
                return -1;
            }

            return accumulator;
        }

        if (ins.getOperation() == jmp) {
            bootI += ins.getValue();
        } else {
            if (ins.getOperation() == acc) {
                accumulator += ins.getValue();
            }

            bootI++;
        }

        ins.setRun();

        if (bootSequence.size() <= bootI) {
            return accumulator;
        }
    }
}

int ItsSoBad(string text_file) {
    string line;
    ifstream input_file(text_file);

    vector<Instruction> bootSequence;

    // Load boot sequence into memory
    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            int numValue = stoi(line.substr(4));
            bootSequence.push_back(Instruction(line.substr(0, 3), numValue));
        }
        
        input_file.close();
    }

    // Not sure if best approach but it takes less than half a second
    if (bruteForce) {
        for (int i = 0; i < bootSequence.size(); i++) {
            vector<Instruction> bootSeqCopy(bootSequence);

            if (bootSeqCopy[i].getOperation() == nop || bootSeqCopy[i].getOperation() == jmp) {
                bootSeqCopy[i].switchJmpNop();
                int acc = runBootSequence(bootSeqCopy, true);
                if (acc != -1) {
                    return acc; 
                }
            }
        }        
    }

    return runBootSequence(bootSequence);
}

int main() {
    // Part One
    bruteForce = false;
    cout << "Part One Answer: " << ItsSoBad("input") << endl;

    // // Part Two
    bruteForce = true;
    cout << "Part Two Answer: " << ItsSoBad("input") << endl;
    
    return 0;
}
