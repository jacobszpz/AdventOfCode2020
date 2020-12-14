#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace ::std;

// set to false for part one
bool gUseWaypoint = false;

enum Action {
    move_north,
    move_east,
    move_south,
    move_west,
    turn_left,
    turn_right,
    move_forward
};

Action actionFromChar(char c) {
    switch (c) {
        case 'N':
            return move_north;
        case 'S':
            return move_south;
        case 'E':
            return move_east;
        case 'W':
            return move_west;
        case 'L':
            return turn_left;
        case 'R':
            return turn_right;
        case 'F':
            return move_forward;
    }

    return move_forward;
}

struct Instruction {
    Action action;
    int moveBy;

    Instruction(string line) {
        moveBy = stoi(line.substr(1));
        action = actionFromChar(line[0]);
    }
};

int getAbsSteps(int nCards, int moveBy, bool pos = true) {
    const int kNDeg = 90;
    int turn = (pos) ? 1 : -1;
    int relSteps = turn * (moveBy / kNDeg);
    int absSteps = (nCards + relSteps) % nCards;
    return absSteps;
}

int getNewFacing(int moveBy, int facing, bool pos = true) {
    const int kNCards = 4;
    int newFacing = (facing + getAbsSteps(kNCards, moveBy, pos)) % kNCards;
    return newFacing;
}

int getManhattan(vector<Instruction> instructions) {
    Action facing = move_east;
    int x = 0, y = 0;

    for (Instruction &ins : instructions) {
        bool move = false;
        bool turnSign = true;
        Action direction;

        switch (ins.action) {
            case turn_right:
                break;
            case turn_left:
                turnSign = false;
                break;
            case move_forward:
                direction = facing;
                move = true;
                break;
            default:
                direction = ins.action;
                move = true;
                break;
        }
    
        if (move) {
            switch (direction) {
                case move_north:
                    y += ins.moveBy;
                    break;
                case move_south:
                    y -= ins.moveBy;
                    break;
                case move_east:
                    x += ins.moveBy;
                    break;
                case move_west:
                    x -= ins.moveBy;
                    break;
            }
        } else {
            facing = Action(getNewFacing(ins.moveBy, facing, turnSign));
        }
    }

    return abs(x) + abs(y);
}

int getWaypointManhattan(vector<Instruction> instructions) {
    int x = 0, y = 0, wX = 10, wY = 1;
    const int kNCards = 4;

    for (Instruction &ins : instructions) {
        bool moveWp = false, rotateWp = true, turnSign = true;
        Action direction;

        switch (ins.action) {
            case turn_right:
                break;
            case turn_left:
                turnSign = false;
                break;
            case move_forward:
                x += (wX * ins.moveBy);
                y += (wY * ins.moveBy);

                rotateWp = false;
                break;
            default:
                direction = ins.action;
                moveWp = true;
                break;
        }

        if (moveWp) {
            switch (direction) {
                case move_north:
                    wY += ins.moveBy;
                    break;
                case move_south:
                    wY -= ins.moveBy;
                    break;
                case move_east:
                    wX += ins.moveBy;
                    break;
                case move_west:
                    wX -= ins.moveBy;
                    break;
            }
        } else if (rotateWp) {
            int turnTimes = getAbsSteps(kNCards, ins.moveBy, turnSign);

            for (int i = 0; i < turnTimes; ++i) {
                int wX_C = wX;
                wX = wY;
                wY = -wX_C;
            }

        }

    }

    return abs(x) + abs(y);
}

int Battleship(string text_file) {
    string line;
    ifstream input_file(text_file);
    vector<Instruction> instructions;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            instructions.push_back(Instruction(line));
        }
        
        input_file.close();
    }

    if (gUseWaypoint) {
        return getWaypointManhattan(instructions);
    }

    return getManhattan(instructions);
}

int main() {
    // Part One
    gUseWaypoint = false;
    cout << "Part One Answer: " << Battleship("input") << endl;

    // Part Two
    gUseWaypoint = true;
    cout << "Part Two Answer: " << Battleship("input") << endl;
    return 0;
}
