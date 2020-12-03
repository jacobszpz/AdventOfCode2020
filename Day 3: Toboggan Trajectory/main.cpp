#include <string>
#include <iostream>
#include <fstream>

using namespace ::std;

int Slider(string text_file) {
    string line;
    ifstream input_file(text_file);

    int trees, x, y = 0;
    int x_move = 1;
    int y_move = 2;

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
    cout << Slider("input") << endl;
    return 0;
}
