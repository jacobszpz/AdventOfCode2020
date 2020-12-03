#include <string>
#include <iostream>
#include <fstream>

using namespace ::std;

int MissionReport(string text_file) {
    string line;
    int year = 2020;
    int line_total = 200;
    
    ifstream input_file(text_file);
    int expense_input[line_total] = {};
    
    // Copy file contents to array
    if (input_file.is_open()) {
        int i = 0;
        while (getline(input_file, line)) {
            expense_input[i] = stoi(line);
            i++;
        }
        input_file.close();
    }
    
    for (int j = 0; j < line_total; j++) {
        int expense = expense_input[j];
        int remainder = year - expense;
        
        for (int k = 0; k < line_total; k++) {
            int complement = expense_input[k];
            int remainder_2 = remainder - complement;
            
            if (complement < remainder) {
                for (int l = 0; l < line_total; l++) {
                    int complement_2 = expense_input[l];
                    
                    if (complement_2 == remainder_2) {
                        cout << expense << ", " << complement << ", " << complement_2 << endl;
                    }
                }
            }
        }
    }
    
    return 0;
}

int main() {
    MissionReport("input");
    return 0;
}
