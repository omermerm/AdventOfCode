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


int extract_and_sum_nums(string& data, bool avoid_red) {
    int acc = 0;
    string cur_num = "";
    vector<char> par_stack{};
    vector<bool> is_red{};
    vector<int> val_at_opening{};
    for (int i = 0; i < data.size(); i++) {
        char c = data[i];

        if (isdigit(c) or c == '-') {
                cur_num += c;
            } else if (cur_num != "") {
                    acc += stoi(cur_num);
                    cur_num = "";
            } else {}

        switch (data[i])
        {
        case '{':
            par_stack.push_back(c);
            is_red.push_back(false);
            val_at_opening.push_back(acc);
            break;

        case '}':
            par_stack.pop_back();
            if (avoid_red & is_red.back()) {
                acc = val_at_opening.back();
            }
            is_red.pop_back();
            val_at_opening.pop_back();
            break;

        case ':':
            if (!is_red.back() & i+5 < data.size() && data.substr(i, 6) == ":\"red\"") {
                is_red.back() = true;
            }
            break;

        default:
            break;
        }
        
    }

    if (cur_num != "") { acc += stoi(cur_num); }
    return acc;
}


int main() {
    string filename = "Day12-input.txt";
    vector<string> lines;
    read_file(lines, filename);
    cout << "Sum of all numbers in JSON: " << extract_and_sum_nums(lines[0], false) << endl;
    cout << "Sum of all non-red numbers in JSON: " << extract_and_sum_nums(lines[0], true) << endl;
    

    return 0;
}