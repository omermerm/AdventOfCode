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
        string name = split_line[0];
        data[name]["speed"] = stoi(split_line[3]);
        data[name]["duration"] = stoi(split_line[6]);
        data[name]["rest"] = stoi(split_line[13]);
    }
    return;
    
}

int distance_traveled(map<string, int>& deer, int time) {
    int cycle_length = deer["duration"] + deer["rest"];
    int cycle_dist = deer["duration"]*deer["speed"];
    int cycles = time / cycle_length;
    int partial_cycle_dist = min(deer["duration"], time % cycle_length)*deer["speed"];

    return cycles*cycle_dist + partial_cycle_dist;
}

map<string, int> distance_traveled(map<string, map<string, int>>& deers, int time) {
    map<string, int> distances{};
    for (auto& deer : deers) {
        distances[deer.first] = distance_traveled(deer.second, time);
    }
    return distances;
}

map<string, int> score_deers(map<string, map<string, int>>& deers, int time) {
    map<string, int> scores{};
    int cur_dist = 0;
    for (int t = 1; t <= time; t++) {
        map<string, int> distances = distance_traveled(deers, t);
        for (auto& deer : distances) {
            cur_dist = max(cur_dist, deer.second);
        }
         for (auto& deer : distances) {
            if (deer.second == cur_dist) {
                scores[deer.first] += 1;
            } 
        }
    }
    return scores;
}

int main() {
    string filename = "Day14-input.txt";
    const int TIME = 2503; //This value appeared on the webpage (not as part of personalized input)
    map<string, map<string, int>> deers{}; //I know the plural of 'deer' is 'deer'...
    parse_data(deers, filename);
    map<string, int> distances = distance_traveled(deers, TIME);
    pair<string, int> farthest("uninitialized", 0);
    for (auto& deer : distances) {
        if (deer.second > farthest.second) {
            farthest = deer;
    }}
    cout << "The maximal distance traveled by a reindeer in " << TIME << " seconds was " << farthest.second << " km, traveled by " << farthest.first << endl;
    map<string, int> scores = score_deers(deers, TIME);
    pair<string, int> winner ("NA", 0);
    for (auto& deer : scores) {
        if (deer.second > winner.second) {
            winner = deer;
        }
    }
    cout << "The maximal score achieved by a reindeer in " << TIME << " seconds was " << winner.second << " points, achieved by " << winner.first << endl;
    

    return 0;
}