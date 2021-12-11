#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

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

vector<string> split(string input, string delim) {
    vector<string> substrings{};
    size_t pos = 0;
    while ((pos = input.find(delim)) != string::npos) {
        substrings.push_back(input.substr(0, pos));
        input.erase(0, pos + delim.length());
    }
    substrings.push_back(input);
    return substrings;
}

void parse_data(map<string, map<string, int>>& data, string filename) {
    vector<string> lines{};
    read_file(lines, filename);
    for (string line : lines) {
        vector<string> split_line = split(line, " ");
        int hap_gain = stoi(split_line[3]); 
        if (split_line[2] == "lose") { hap_gain = -hap_gain; }
        string gainer = split_line[0];
        string neighbor = split_line[10];
        neighbor.pop_back();

        data[gainer][neighbor] = hap_gain;
    }
    return;
    
}

int configuration_value(vector<string> permutation, map<string, map<string, int>>& hap_vals) {
    int total_hap = 0;
    for (int i = 0; i < permutation.size()-1; i++) {
        total_hap += hap_vals[permutation[i]][permutation[i+1]] + hap_vals[permutation[i+1]][permutation[i]];
    }
    return total_hap;
}

int happiest_seating(map<string, map<string, int>>& hap_vals, bool circular) {
    vector<string> guests{};
    for (auto& entry : hap_vals) {guests.push_back(entry.first);} // make a vector of guests
    sort(guests.begin(), guests.end());
    if (circular) { guests.push_back(guests[0]); }
    int cur_hap = configuration_value(guests, hap_vals);
    if (circular) { guests.pop_back(); }
    int most_happiness = cur_hap;
    
    while(next_permutation(guests.begin(), guests.end())) {
        if (circular) { guests.push_back(guests[0]); }
        cur_hap = configuration_value(guests, hap_vals);
        if (circular) { guests.pop_back(); }
        most_happiness = max(cur_hap, most_happiness);
    }
    
    return most_happiness;
}


int main() {
    string filename = "Day13-input.txt";
    map<string, map<string, int>> hap_vals{};
    parse_data(hap_vals, filename);
    int happiest_circular = happiest_seating(hap_vals, true);
    cout << "The happiest seating arrangement excluding yourself produces " << happiest_circular << " happiness" << endl;
    int happiest_with_you = happiest_seating(hap_vals, false);
    cout << "The happiest seating arrangement including yourself produces " << happiest_with_you << " happiness" << endl;

    return 0;
}