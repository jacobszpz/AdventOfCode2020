#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace ::std;

// set to true for part one
bool gGetErrorRate = false;

enum ReadMode {
    Fields,
    My_Ticket,
    Nearby_Tickets
};

struct ValidRange {
    int start;
    int end;
    ValidRange(int s, int e) : start(s), end(e) {}
    ValidRange(string line) {
        int dashPos = line.find('-');

        string startStr = line.substr(0, dashPos);
        start = stoi(startStr);

        string endStr = line.substr(dashPos + 1);
        end = stoi(endStr);
    }
};

struct TicketField {
    int index;
    string name;
    vector<ValidRange> vRanges;

    TicketField(string line) {
        string orDelim = " or ";
        string colonDelim = ": ";

        int colonPos = line.find(colonDelim);
        name = line.substr(0, colonPos);

        colonPos += colonDelim.length();

        int orPos = line.find(orDelim);
        int firstRangeL = orPos - colonPos;

        vRanges.push_back(ValidRange(line.substr(colonPos, firstRangeL)));
        vRanges.push_back(ValidRange(line.substr(orPos + orDelim.length())));
    }

    TicketField() {}
};

vector<int> parseNumLine(string line, char delim = ',') {
    vector<int> nums;
    int currentPos = 0, delimPos;

    do {
        line = line.substr(currentPos);
        delimPos = line.find(delim);

        if (delimPos == -1) {
            delimPos = line.length();
        }

        nums.push_back(stoi(line.substr(0, delimPos)));
        currentPos = delimPos + 1;
    } while (currentPos < line.length());

    return nums;
}

unsigned long int LostInTranslation(string text_file) {
    string line;
    ifstream input_file(text_file);

    ReadMode mode = Fields;
    const string myTicketTitle = "your ticket:";
    const string nearbyTicketsTitle = "nearby tickets:";

    typedef vector<int> Ticket;
    typedef vector<TicketField> FieldCollection;

    Ticket myTicket;
    vector<Ticket> nearbyTickets;
    vector<Ticket> validTickets;
    FieldCollection fields;
    vector<ValidRange> allRanges;

    if (input_file.is_open()) {
        while (getline(input_file, line)) {
            if (line == myTicketTitle) {
                mode = My_Ticket;
            } else if (line == nearbyTicketsTitle) {
                mode = Nearby_Tickets;
            } else if (line != "") {
                if (mode == Fields) {
                    fields.push_back(TicketField(line));

                    for (auto range : fields.back().vRanges) {
                        allRanges.push_back(range);
                    }
                } else if (mode == My_Ticket) {
                    myTicket = parseNumLine(line);
                } else if (mode == Nearby_Tickets) {
                    nearbyTickets.push_back(parseNumLine(line));
                }
            }
        }
        
        input_file.close();
    }

    // Get count of invalid fields, build vector of valid tickets
    vector<int> invalid;

    for (Ticket &nearby : nearbyTickets) {
        bool ticketValid = true;

        for (int &value : nearby) {
            bool valueValid = false;

            for (ValidRange &range : allRanges) {
                if (value >= range.start && value <= range.end) {
                    valueValid = true;
                }
            }

            if (!valueValid) {
                ticketValid = false;
                invalid.push_back(value);
            }
        }

        if (ticketValid) {
            validTickets.push_back(nearby);
        }
    }

    // Return error rate if only doing part one
    if (gGetErrorRate) {
        int errorRate = 0;

        for (int &value : invalid) {
            errorRate += value;
        }

        return errorRate;
    }

    // Get nested vector of possible fields for every column
    vector<FieldCollection> possibleMatches;

    for (int i = 0; i < validTickets[0].size(); ++i) {
        FieldCollection oldMatches = fields, matches;

        for (Ticket &valid : validTickets) {
            int value = valid[i];

            for (TicketField &field : oldMatches) {
                bool validField = false;

                for (ValidRange &range : field.vRanges) {
                    if (value >= range.start && value <= range.end) {
                        validField = true;
                    }
                }

                if (validField) {
                    matches.push_back(field);
                }
            }

            oldMatches = matches;
            matches.clear();
        }

        possibleMatches.push_back(oldMatches);
    }

    // When column can only be a single field
    // assign and remove from other column candidates list
    map<int, TicketField> definiteMatches;
    vector<FieldCollection> old = possibleMatches, current;
    TicketField match, lastMatch;
    
    while (definiteMatches.size() < possibleMatches.size()) {
        // For index
        int j = 0;

        for (FieldCollection &coll : old) {
            FieldCollection newColl;

            // For candidates
            if (coll.size() == 1) {
                definiteMatches[j] = coll[0];
                match = coll[0];
            } else {
                for (TicketField &field : coll) {
                    if (field.name != lastMatch.name) {
                        newColl.push_back(field);
                    }
                }
            }

            current.push_back(newColl);
            j++;
        }

        old = current;
        current.clear();
        lastMatch = match;
    }

    // Save indexes of rows which start with 'departure'
    vector<int> departureRows;
    string departed = "departure";

    for (auto &itr : definiteMatches) {
        string &fieldName = itr.second.name;

        if (fieldName.substr(0, departed.length()) == departed) {
            departureRows.push_back(itr.first);
        }
    }

    // From previous indexes get said fields from my ticket
    // then multiply together
    unsigned long int theDeparted = 1;
    for (int fieldI : departureRows) {
        theDeparted *= myTicket[fieldI];
    }

    return theDeparted;
}

int main() {
    // Part One
    gGetErrorRate = true;
    cout << "Part One Answer: " << LostInTranslation("input") << endl;

    // Part Two
    gGetErrorRate = false;
    cout << "Part Two Answer: " << LostInTranslation("input") << endl;
    return 0;
}
