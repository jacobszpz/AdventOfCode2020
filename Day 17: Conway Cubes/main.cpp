#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace ::std;

typedef vector<char> Row;
typedef vector<Row> Slice;
typedef vector<Slice> Tess;

// set to true for part one
bool gOnlyThreeD = false;

// Advances the tesseract one cycle forward
vector<Slice> simCycle(vector<Slice> tess) {
    const int radius = 1;
    const char off = '.', on = '#';
    int oldTSize, oldSSize, oldRSize, oldCenter, tSize, sSize, rSize;
    vector<Slice> newTess;

    oldTSize = tess.size();
    oldSSize = tess[0].size();
    oldRSize = tess[0][0].size();

    tSize = oldTSize + 2; 
    sSize = oldSSize + 2;
    rSize = oldRSize + 2;

    // Iterate over a cube that's two units larger in every dimension
    // First, iterate over every unit in the cube, then, iterate over
    // the valid neighbour units, counting those which are on

    // Over slices
    for (int newSlice = 0; newSlice < tSize; ++newSlice) {
        Slice slc;

        int relS = newSlice - (tSize / 2);
        //cout << endl << "Building slice " << relS << endl << endl;

        // Over rows in slice
        for (int newRow = 0; newRow < sSize; ++newRow) {
            Row row;

            int relR = newRow - (sSize / 2);
            //cout << "Building row " << relR << endl;

            // Over chars in row
            for (int newChar = 0; newChar < rSize; ++newChar) {
                int onCount = 0;
                bool active = false;

                int relC = newChar - (rSize / 2);
                //cout << "Building char at " << relC << endl;

                // Iterate over neighbouring slices
                for (int s = -radius; s <= radius; ++s) {
                    int realS = relS + s + (oldTSize / 2);

                    // If slice exists in current tesseract
                    if (realS >= 0 && realS < oldTSize) {

                        // Iterate over neighbouring rows
                        for (int r = -radius; r <= radius; ++r) {
                            int realR = relR + r + (oldSSize / 2);

                            // If slice exists in current tesseract
                            if (realR >= 0 && realR < oldSSize) {

                                // Iterate over neighbouring chars
                                for (int c = -radius; c <= radius; ++c) {
                                    int realC = relC + c + (oldRSize / 2);

                                    if (realC >= 0 && realC < oldRSize) {
                                        char accessed = tess[realS][realR][realC];
                                        bool currentOn = (accessed == on);

                                        if (!s && !r && !c) {
                                            active = currentOn;
                                            //cout << "Same unit " << active << endl;
                                        } else {
                                            onCount += currentOn;
                                        }
                                        //cout << "For " << newSlice << ", " << newRow << ", " << newChar << endl;
                                        //cout << "Accessed " << realS << ", " << realR << ", " << realC << endl;
                                    }
                                }
                            }
                        }
                    }
                }

                char cubeState = off;

                // Somehow get on/off state from actual cube
                if (active && onCount >= 2 && onCount <= 3) {
                    cubeState = on;
                // If inactive but three neighbours are active
                } else if (!active && onCount == 3) {
                    cubeState = on;
                }

                row.push_back(cubeState);
            }

            for (char a : row) {
//                cout << a;
            }
            //cout << endl;

            slc.push_back(row);
        }

        newTess.push_back(slc);
    }

    return newTess;
}

// Advances the tesseract one cycle forward
vector<Tess> sim4DCycle(vector<Tess> tetra) {
    const int radius = 1;
    const char off = '.', on = '#';
    int oldQSize, oldTSize, oldSSize, oldRSize, qSize, tSize, sSize, rSize;
    vector<Tess> newTetra;

    oldQSize = tetra.size();
    oldTSize = tetra[0].size();
    oldSSize = tetra[0][0].size();
    oldRSize = tetra[0][0][0].size();

    qSize = oldQSize + 2;
    tSize = oldTSize + 2;
    sSize = oldSSize + 2;
    rSize = oldRSize + 2;

    for (int newTess = 0; newTess < qSize; ++newTess) {
        Tess tsr;

        int relT = newTess - (qSize / 2);

        for (int newSlice = 0; newSlice < tSize; ++newSlice) {
            Slice slc;

            int relS = newSlice - (tSize / 2);
            //cout << endl << "Building slice " << relS << endl << endl;

            // Over rows in slice
            for (int newRow = 0; newRow < sSize; ++newRow) {
                Row row;

                int relR = newRow - (sSize / 2);
                //cout << "Building row " << relR << endl;

                // Over chars in row
                for (int newChar = 0; newChar < rSize; ++newChar) {
                    int onCount = 0;
                    bool active = false;

                    int relC = newChar - (rSize / 2);
                    //cout << "Building char at " << relC << endl;

                    for (int t = -radius; t <= radius; ++t) {
                        int realT = relT + t + (oldQSize / 2);

                        // If tess exists in current tesseract
                        if (realT >= 0 && realT < oldQSize) {

                            // Iterate over neighbouring slices
                            for (int s = -radius; s <= radius; ++s) {
                                int realS = relS + s + (oldTSize / 2);

                                // If slice exists in current tesseract
                                if (realS >= 0 && realS < oldTSize) {

                                    // Iterate over neighbouring rows
                                    for (int r = -radius; r <= radius; ++r) {
                                        int realR = relR + r + (oldSSize / 2);

                                        // If slice exists in current tesseract
                                        if (realR >= 0 && realR < oldSSize) {

                                            // Iterate over neighbouring chars
                                            for (int c = -radius; c <= radius; ++c) {
                                                int realC = relC + c + (oldRSize / 2);

                                                if (realC >= 0 && realC < oldRSize) {
                                                    char accessed = tetra[realT][realS][realR][realC];
                                                    bool currentOn = (accessed == on);

                                                    if (!s && !r && !c && !t) {
                                                        active = currentOn;
                                                        //cout << "Same unit " << active << endl;
                                                    } else {
                                                        onCount += currentOn;
                                                    }
                                                    //cout << "For " << newSlice << ", " << newRow << ", " << newChar << endl;
                                                    //cout << "Accessed " << realS << ", " << realR << ", " << realC << endl;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    char cubeState = off;

                    // Somehow get on/off state from actual cube
                    if (active && onCount >= 2 && onCount <= 3) {
                        cubeState = on;
                    // If inactive but three neighbours are active
                    } else if (!active && onCount == 3) {
                        cubeState = on;
                    }

                    row.push_back(cubeState);
                }

                for (char a : row) {
    //                cout << a;
                }
                //cout << endl;

                slc.push_back(row);
            }
            tsr.push_back(slc);
        }

        newTetra.push_back(tsr);
    }

    return newTetra;
}

int countTess(vector<Slice> tess) {
    bool print = false;
    int si = 0, onCount = 0;

    for (Slice slc : tess) {
        //cout << endl << "Slice " << si << endl;
        for (Row row : slc) {
            for (char c : row) {
                /*cout << c;*/

                onCount += c == '#';
            }
            //cout << endl;
        }

        si++;
    }

    //cout << "on " << onCount << endl;
    return onCount;
}

int countTetra(vector<Tess> tetra) {
    int z, w = 0, onCount = 0;

    for (Tess tess: tetra) {
        z = 0;
        for (Slice slc : tess) {
            //cout << endl << "z=" << z << " w=" << w << endl;
            for (Row row : slc) {
                for (char c : row) {
                    //cout << c;

                    onCount += c == '#';
                }
                //cout << endl;
            }

            z++;
        }

        w++;
    }  

    //cout << "on " << onCount << endl;
    return onCount;
}

int Tesseract(string text_file) {
    string line;
    ifstream input_file(text_file);

    vector<Tess> tetra;

    Tess tess;
    Slice iSlice;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            Row lRow;

            for (char c : line) {
                lRow.push_back(c);   
            }

            iSlice.push_back(lRow);
        }
        
        input_file.close();
    }

    tess.push_back(iSlice);
    tetra.push_back(tess);


    for (int i = 0; i < 6; ++i) {
        tess = simCycle(tess);
    }

    if (gOnlyThreeD) {
        return countTess(tess);
    }

    for (int i = 0; i < 6; ++i) {
        tetra = sim4DCycle(tetra);
    }

    return countTetra(tetra);
}

int main() {
    // Part One
    gOnlyThreeD = true;
    cout << "Part One Answer: " << Tesseract("input") << endl;

    // Part Two
    gOnlyThreeD = false;
    cout << "Part Two Answer: " << Tesseract("input") << endl;
    return 0;

    // I may live to see the day when I fix this mess, but that day is not today
}
