#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void read_file(vector<string> &lines, string filename) {
    ifstream file (filename);
    while(file.good()) {
        string line;
        getline(file, line);
        lines.push_back(line);
    }
    file.close();
    return;
}


bool validate_pass(string& pass) {
    bool straight = false;
    //increasing straight
    for (int i = 0; i < pass.size() - 3; i++) {
        if (pass[i+1] == pass[i]+1 & pass[i+2] == pass[i]+2) {
            straight = true;
            break;
        }
    }
    if (!straight) { return false; }

    //no i, o, or l
    bool noiol = true;
    for (int i = 0; i < pass.size(); i++) {
        if (pass[i] == 'i' | pass[i] == 'o' | pass[i] == 'l') {
            noiol = false;
            break;
        }
    }
    if (!noiol) { return false; }

    bool pair_one = false, pair_two = false;
    //two non-overlapping pairs of identical letters
    for (int i = 1; i < pass.size(); i++) {
        if (pass[i] == pass[i-1]) {
            if (!pair_one) {
                pair_one = true;
                i++;
            } else {
                pair_two = true;
                break;
            }
        }
    }
    return pair_two;
}

void increase_pass(string& pass) {
    for (int i = pass.size()-1; i >= 0; i--) {
        if (pass[i] < 'z') {
            pass[i]++;
            break;
        } else {
            pass[i] = 'a';
        }
    }
}

void change_to_next_valid_pass(string& pass) {
    while(!validate_pass(pass)) {
        increase_pass(pass);
    }
}

int main() {
    string filename = "Day11-input.txt";
    vector<string> lines;
    read_file(lines, filename);
    string pass = lines[0];
    change_to_next_valid_pass(pass);
    cout << "Next valid password: " << pass << endl;
    increase_pass(pass);
    change_to_next_valid_pass(pass);
    cout << "Next valid password after that: " << pass << endl;

    return 0;
}