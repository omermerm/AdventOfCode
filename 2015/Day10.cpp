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

string process_string(string s, int times) {
    for (int time; time < times; time++) {
        string new_s = "";
        char cur_char = s[0];
        int cur_amt = 1;
        for (int i = 1; i < s.size(); i++) {
            if (cur_char == s[i]) {
                cur_amt += 1;
            } else {
                new_s += to_string(cur_amt) + cur_char;
                cur_char = s[i];
                cur_amt = 1;
            }
        }
        new_s += to_string(cur_amt) + cur_char;
        s = new_s;
    }
    return s;
}


int main() {
    string filename = "Day10-input.txt";
    vector<string> lines;
    read_file(lines, filename);
    string initial_string = lines[0];
    string forty = process_string(initial_string, 40);
    string fifty = process_string(forty, 10);
    cout << "The length of the input string after processing it 40 times: " << forty.size() << endl;
    cout << "The length of the input string after processing it 50 times: " << fifty.size() << endl;

    return 0;
}