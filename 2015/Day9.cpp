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
        int dist = stoi(split_line[4]);
        data[split_line[0]][split_line[2]] = dist;
        data[split_line[2]][split_line[0]] = dist;
    }
    return;
    
}

int get_dist(vector<string> permutation, map<string, map<string, int>>& dists) {
    int total_dist = 0;
    for (int i = 0; i < permutation.size()-1; i++) {
        total_dist += dists[permutation[i]][permutation[i+1]];
    }
    return total_dist;
}

pair<int, int> best_distances(map<string, map<string, int>>& dists) {
    vector<string> locations{};
    for (auto& entry : dists) {locations.push_back(entry.first);} // make a vector of locations
    sort(locations.begin(), locations.end());
    int cur_dist = get_dist(locations, dists);
    int shortest = cur_dist;
    int longest = cur_dist;
    
    while(next_permutation(locations.begin(), locations.end())) {
        cur_dist = get_dist(locations, dists);
        shortest = min(cur_dist, shortest);
        longest = max(cur_dist, longest);
    }
    
    return pair<int, int> (shortest, longest);
}


int main() {
    string filename = "Day9-input.txt";
    map<string, map<string, int>> dists{};
    parse_data(dists, filename);
    pair<int, int> best = best_distances(dists);
    cout << "The shortest distance traveled when visiting each location exactly once: " << best.first << endl;
    cout << "The shortest distance traveled when visiting each location exactly once: " << best.second << endl;

    return 0;
}