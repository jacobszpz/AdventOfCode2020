#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace ::std;

// set to true for part one
bool gSamePriority = false;

long long int applyOperation(char operand, long long int a, long long int b) {
    switch (operand) {
        case '+':
            return a + b;
        case '*':
            return a * b;
    }

    return -1;
}

long long int parseExpression(string expr) {
    // parse from left to right, use recursion for parenthesis'd sections and replace
    char op = '?';
    long long int r = 0, n, l = 0;
    string sub;

    for (char c : expr) {
        switch (c) {
            case '(':
                l++;
                break;
            case ')':
                l--;
                break;
        }

        if (l) {
            sub += c;
        } else {
            switch (c) {
                case '+':
                case '*':
                    op = c;
                    break;
                case ' ':
                    break;
                case ')':
                    n = parseExpression(sub.substr(1, sub.length() - 1));

                    if (op != '?') {
                        r = applyOperation(op, r, n);
                    } else {
                        r = n;
                    }

                    sub = "";
                    break;
                default:
                    n = c - '0';

                    if (op != '?') {
                        r = applyOperation(op, r, n);
                    } else {
                        r = n;
                    }
                    break;
            }
        }
    }

    return r;
}

long long int parseExprAddition(string expr) {
    // I have no idea how this worked
    char op = '?';
    long long int r = 0, n, l = 0, mR = 1;
    string sub;

    vector<long long int> mult;

    for (char c : expr) {
        switch (c) {
            case '(':
                l++;
                break;
            case ')':
                l--;
                break;
        }

        if (l) {
            sub += c;
        } else {
            switch (c) {
                case '+':
                    op = c;
                    break;
                case '*':
                    mult.push_back(r);
                    op = '?';
                case ' ':
                    break;
                case ')':
                    n = parseExprAddition(sub.substr(1, sub.length() - 1));

                    if (op != '?') {
                        r = applyOperation(op, r, n);
                    } else {
                        r = n;
                    }

                    sub = "";
                    break;
                default:
                    n = c - '0';

                    if (op != '?') {
                        r = applyOperation(op, r, n);
                    } else {
                        r = n;
                    }
                    break;
            }
        }
    }

    for (long long int m : mult) {
        mR *= m;
    }

    mR *= r;

    return mR;
}

long long int MathIsMath(string text_file) {
    string line;
    ifstream input_file(text_file);

    long long int sum = 0;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            long int r = 0;
            if (gSamePriority) {
                r = parseExpression(line);
            } else {
                r = parseExprAddition(line);
            }

            sum += r;
        } 
        
        input_file.close();
    }
    
    return sum;
}

int main() {
    // Part One
    gSamePriority = true;
    cout << "Part One Answer: " << MathIsMath("input") << endl;

    // Part Two
    gSamePriority = false;
    cout << "Part Two Answer: " << MathIsMath("input") << endl;
    return 0;
}
