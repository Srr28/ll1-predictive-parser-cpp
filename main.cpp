#include <bits/stdc++.h>
using namespace std;

using Grammar = unordered_map<char, vector<string>>;
using Sets = unordered_map<char, set<char>>;

Grammar grammar;
Sets FIRST, FOLLOW;
set<char> nonTerminals, terminals;
map<pair<char, char>, string> table;

bool isNonTerminal(char c) {
    return nonTerminals.count(c);
}

set<char> firstOfString(const string& s) {
    set<char> result;

    if (s == "#") {
        result.insert('#');
        return result;
    }

    bool epsilonPossible = true;

    for (char c : s) {
        if (!epsilonPossible) break;
        epsilonPossible = false;

        if (!isNonTerminal(c)) {
            result.insert(c);
        } else {
            for (char x : FIRST[c]) {
                if (x != '#') result.insert(x);
            }
            if (FIRST[c].count('#')) epsilonPossible = true;
        }
    }

    if (epsilonPossible) result.insert('#');
    return result;
}

void calculateFIRST() {
    bool changed = true;

    while (changed) {
        changed = false;

        for (auto& [lhs, productions] : grammar) {
            for (const string& rhs : productions) {
                set<char> temp = firstOfString(rhs);

                for (char c : temp) {
                    if (FIRST[lhs].insert(c).second)
                        changed = true;
                }
            }
        }
    }
}

void calculateFOLLOW(char start) {
    FOLLOW[start].insert('$');
    bool changed = true;

    while (changed) {
        changed = false;

        for (auto& [lhs, productions] : grammar) {
            for (const string& rhs : productions) {
                for (int i = 0; i < static_cast<int>(rhs.size()); i++) {
                    char B = rhs[i];
                    if (!isNonTerminal(B)) continue;

                    string beta = rhs.substr(i + 1);
                    set<char> firstBeta = firstOfString(beta);

                    for (char c : firstBeta) {
                        if (c != '#' && FOLLOW[B].insert(c).second)
                            changed = true;
                    }

                    if (beta.empty() || firstBeta.count('#')) {
                        for (char c : FOLLOW[lhs]) {
                            if (FOLLOW[B].insert(c).second)
                                changed = true;
                        }
                    }
                }
            }
        }
    }
}

bool constructTable() {
    bool conflict = false;

    for (auto& [lhs, productions] : grammar) {
        for (const string& rhs : productions) {
            set<char> first = firstOfString(rhs);

            for (char c : first) {
                if (c == '#') continue;

                auto key = make_pair(lhs, c);
                if (table.count(key) && table[key] != rhs)
                    conflict = true;
                else
                    table[key] = rhs;
            }

            if (first.count('#')) {
                for (char c : FOLLOW[lhs]) {
                    auto key = make_pair(lhs, c);
                    if (table.count(key) && table[key] != rhs)
                        conflict = true;
                    else
                        table[key] = rhs;
                }
            }
        }
    }

    return !conflict;
}

void displaySets() {
    cout << "\nFIRST SETS:\n";
    for (char c : nonTerminals) {
        cout << "FIRST(" << c << ") = { ";
        for (char x : FIRST[c]) cout << x << " ";
        cout << "}\n";
    }

    cout << "\nFOLLOW SETS:\n";
    for (char c : nonTerminals) {
        cout << "FOLLOW(" << c << ") = { ";
        for (char x : FOLLOW[c]) cout << x << " ";
        cout << "}\n";
    }
}

void displayTable() {
    cout << "\nPREDICTIVE PARSING TABLE:\n";
    for (char nt : nonTerminals) {
        for (char t : terminals) {
            cout << "M[" << nt << ", " << t << "] = ";
            if (table.count({nt, t}))
                cout << nt << " -> " << table[{nt, t}];
            else
                cout << "ERROR";
            cout << '\n';
        }

        cout << "M[" << nt << ", $] = ";
        if (table.count({nt, '$'}))
            cout << nt << " -> " << table[{nt, '$'}];
        else
            cout << "ERROR";
        cout << '\n';
    }
}

bool parse(string input, char start) {
    input += '$';

    stack<char> st;
    st.push('$');
    st.push(start);

    size_t i = 0;
    cout << "\nSTACK\t\tINPUT\t\tACTION\n";

    while (!st.empty()) {
        char top = st.top();
        char current = input[i];

        stack<char> temp = st;
        string stackStr;
        while (!temp.empty()) {
            stackStr += temp.top();
            temp.pop();
        }
        reverse(stackStr.begin(), stackStr.end());

        cout << stackStr << "\t\t" << input.substr(i) << "\t\t";

        if (top == '$' && current == '$') {
            cout << "ACCEPT\n";
            return true;
        }

        if (!isNonTerminal(top)) {
            if (top == current) {
                cout << "Match " << current << '\n';
                st.pop();
                ++i;
            } else {
                cout << "ERROR: Terminal mismatch\n";
                return false;
            }
        } else {
            auto it = table.find({top, current});
            if (it == table.end()) {
                cout << "ERROR: No production found\n";
                return false;
            }

            const string rhs = it->second;
            cout << top << " -> " << rhs << '\n';
            st.pop();

            if (rhs != "#") {
                for (int j = static_cast<int>(rhs.size()) - 1; j >= 0; --j)
                    st.push(rhs[j]);
            }
        }
    }

    return false;
}

int main() {
    int n;
    cout << "Enter number of non-terminals: ";
    if (!(cin >> n) || n <= 0) {
        cerr << "Invalid number of non-terminals.\n";
        return 1;
    }

    char start = '\0';
    cout << "Enter grammar (LHS number_of_productions RHS...):\n";

    for (int i = 0; i < n; i++) {
        char lhs;
        int count;

        if (!(cin >> lhs >> count) || count <= 0) {
            cerr << "Invalid grammar input.\n";
            return 1;
        }

        if (i == 0) start = lhs;
        nonTerminals.insert(lhs);

        for (int j = 0; j < count; j++) {
            string rhs;
            if (!(cin >> rhs)) {
                cerr << "Missing production.\n";
                return 1;
            }
            grammar[lhs].push_back(rhs);
        }
    }

    for (const auto& [lhs, productions] : grammar) {
        for (const string& rhs : productions) {
            for (char c : rhs) {
                if (c != '#' && !isNonTerminal(c))
                    terminals.insert(c);
            }
        }
    }

    calculateFIRST();
    calculateFOLLOW(start);
    displaySets();

    if (!constructTable()) {
        displayTable();
        cerr << "\nGrammar is not LL(1): parsing-table conflict detected.\n";
        return 1;
    }

    displayTable();

    string input;
    cout << "\nEnter input string: ";
    cin >> input;

    cout << (parse(input, start) ? "\nString ACCEPTED\n"
                                 : "\nString REJECTED\n");
    return 0;
}
