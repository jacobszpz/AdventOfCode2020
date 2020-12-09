#include <string>
#include <iostream>
#include <fstream>

using namespace ::std;

int Slider(string text_file, int x_move, int y_move) {
    string line;
    ifstream input_file(text_file);

    int trees = 0, x = 0, y = 0;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            if (!(y % y_move)) {
                trees += (line[x % line.length()] == '#');
                x += x_move;
            }
            y++;
        }
        
        input_file.close();
    }
    return trees;
}

int main() {
    // Not meant for direct modification
    int x_move;
    int y_move = 1;

    int treeList[5] = {};
    long int product = 1;

    for (int i = 0; i < 5; i++) {
        if (i < 4) {
            x_move = (i * 2) + 1;
        } else {
            x_move = 1;
            y_move = 2;
        }

        treeList[i] = Slider("input", x_move, y_move);
        product *= treeList[i];

        cout << "Trees found with x" << x_move << " y" << y_move;
        cout << ": " << treeList[i] << endl;
    }

    cout << "Part One Answer: " << treeList[1] << endl;
    cout << "Part Two Answer: " << product << endl;
    return 0;
}
