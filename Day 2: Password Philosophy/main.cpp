#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

using namespace ::std;

int PassPolicy(string text_file) {
    
    string line;
    ifstream input_file(text_file);
    int valid_pass = 0;

    
    if (input_file.is_open()) {
        
        while (getline(input_file, line)) {
            int colon_pos = line.find(':');
            int dash_pos = line.find('-');

            string password = line.substr(colon_pos + 2, line.length());
            char letter = line[colon_pos - 1];
            
            int start_pos = stoi(line.substr(0, dash_pos));
            int end_pos = stoi(line.substr(dash_pos + 1, colon_pos));            
            
            bool start_valid = (char) password[start_pos - 1] == letter;
            bool end_valid = (char) password[end_pos - 1] == letter;

            if (start_valid != end_valid) {
                cout << password << " is valid" << endl;
                valid_pass++;
            }            
            
        }
        
        input_file.close();
    }
    
    return valid_pass;
}

int main() {
    cout<< PassPolicy("input") << endl;
    return 0;
}
