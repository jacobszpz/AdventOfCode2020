#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace ::std;

// set to 4, true for part one
// 5, false for two
int maxOccupancy = 5;
bool immediate = false;

enum seatState {
    empty,
    occupied,
    floor
};

seatState stateFromChar(char c) {
    switch (c) {
        case '.':
            return floor;
        case 'L':
            return empty;
        case '#':
            return occupied;
    }

    return empty;
}

char stateToChar(seatState s) {
    switch (s) {
        case floor:
            return '.';
        case empty:
            return 'L';
        case occupied:
            return '#';
    }

    return 'L';
}

char getInGrid(vector<char> &grid, int row, int column, int width) {
    int index = (row * width) + column;
    return grid.at(index);
}

vector<char> processGrid(vector<char> &grid, int width) {
    vector<char> processed;
    int cell = 0;
    int radius = 1;
    int rows = (grid.size() / width);

    for (auto &c : grid) {
        int row = cell / width;
        int column = cell % width;

        int adjOccupancy = 0;
        seatState cState = stateFromChar(c);

        if (immediate) {
            int rowBack = max(row - radius, 0);
            int rowForward = min(row + radius, rows - 1);
    
            int columnBack = max(column - radius, 0);
            int columnForward = min(column + radius, width - 1);
    
            if (cState != floor) {
                for (int r = rowBack; r <= rowForward; r++) {
                    for (int l = columnBack; l <= columnForward; l++) {
                        if (r != row || l != column) {
                            char adj = getInGrid(grid, r, l, width);
                            seatState adjState = stateFromChar(adj);
    
                            if (adjState == occupied) {
                                adjOccupancy++;
                            }
                        }
                    }
                }
            }
        } else {
            int directions = 8;
            int x_moves[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
            int y_moves[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

            // Explore all 8 directions
            for (int i = 0; i < directions; i++) {
                int r = row, l = column;

                while (true) {
                    r += y_moves[i];
                    l += x_moves[i];

                    if (r >= rows || l >= width || r < 0 || l < 0) {
                        break;
                    }

                    char adj = getInGrid(grid, r, l, width);
                    seatState adjState = stateFromChar(adj);

                    if (adjState == occupied) {
                        adjOccupancy++;
                    }

                    if (adjState != floor) {
                        break;
                    }
                }
            }
        }

        seatState newState = cState;

        if (cState == empty && !adjOccupancy) {
            newState = occupied;
        } else if (cState == occupied && adjOccupancy >= maxOccupancy) {
            newState = empty;
        }

        processed.push_back(stateToChar(newState));
        cell++;
    }

    return processed;
}

int SitDown(string text_file) {
    string line;
    ifstream input_file(text_file);

    int i = 0;
    int width = 0;
    vector<char> grid;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            width = (!i) ? line.length(): width;
            for (int j = 0; j < line.length(); j++) {
                grid.push_back(line[j]);
            }

            i++;
        }

        input_file.close();
    }

    vector<char> currentRound = grid;
    vector<char> newRound;

    while (true) {
        newRound = processGrid(currentRound, width);

        if (newRound == currentRound) {
            break;
        }

        currentRound = newRound;
    }

    return count(currentRound.begin(), currentRound.end(), '#');
}

int main() {
    // Part One
    maxOccupancy = 4;
    immediate = true;
    cout << "Part One Answer: " << SitDown("input") << endl;

    // Part Two
    maxOccupancy = 5;
    immediate = false;
    cout << "Part Two Answer: " << SitDown("input") << endl;
    return 0;
}
