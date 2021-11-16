#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<string> read_file(string filename) {
    vector<string> lines{};
    ifstream file (filename);
    while(file.good()) {
        string line;
        getline(file, line);
        lines.push_back(line);
    }
    file.close();
    return lines;
}

int line_chars(string line) {
    int excess = 2;
    for (int i = 1; i < line.length()-1; i++) {
        if (line[i] == '\\') {
            switch (line[i+1])
            {
            case 'x':
                excess += 3;
                i += 3;
                break;
            default:
                excess += 1;
                i += 1;
                break;
            }
        }
    }
    return excess;
}

int recode_overhead(string line) {
    int ans = 2;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '\\' or line[i] == '\"') {
            ans += 1;
        }
    }
    return ans;
}

int * countChars(string filename) {
    vector<string> input_lines = read_file(filename);
    int total_excess_code_chars = 0;
    int cumulative_recode_overhead = 0;
    for (int i = 0; i < input_lines.size(); i++){
        total_excess_code_chars += line_chars(input_lines[i]);
        cumulative_recode_overhead += recode_overhead(input_lines[i]);
    }
    static int ans[] = {total_excess_code_chars, cumulative_recode_overhead};
    return ans;
}

int main() {
    int * answers = countChars("Day8-input.txt");
    cout << "Number of excess code chars vs. memory chars: " << answers[0] << endl;
    cout << "Number of excess recode chars vs. code chars: " << answers[1] << endl;
    return 0;
}