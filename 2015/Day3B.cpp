#include <iostream>
#include <fstream>
#include <set>

using namespace std;

void updateLoc(pair<int, int> * loc, char c) {
    switch (c)
        {
        case '>':
            (*loc).first += 1;
            break;
        case '<':
            (*loc).first -= 1;
            break;
        case '^':
            (*loc).second += 1;
            break;
        case 'v':
            (*loc).second -= 1;
            break;
        default:
            break;
        }
}

int housesVisited() {
    ifstream input_file ("Day3-input.txt");
    pair<int,int> initial_loc (0,0);
    pair<int,int> locs[] = {initial_loc, initial_loc}; //locs[0] is santa, locs[1] is robo-santa
    set<pair<int,int>> visited;
    visited.insert(locs[0]);
    int active_santa = 0; // 0 for santa, 1 for robo_santa
    while(input_file.good()) {
        updateLoc(&locs[active_santa], input_file.get());
        visited.insert(locs[active_santa]);
        active_santa = 1 - active_santa;
    }
    input_file.close();
    return visited.size();
}

int main() {
    cout << "Number of unique houses visited: " << housesVisited() << endl;
    return 0;
}