#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int housesVisited() {
    const int X = 0;
    const int Y = 1;
    ifstream input_file ("Day3-input.txt");
    pair<int,int> loc (0,0);
    set<pair<int,int>> visited;
    visited.insert(loc);
    while(input_file.good()) {
        switch (input_file.get())
        {
        case '>':
            loc.first += 1;
            break;
        case '<':
            loc.first -= 1;
            break;
        case '^':
            loc.second += 1;
            break;
        case 'v':
            loc.second -= 1;
            break;
        default:
            break;
        }
        visited.insert(loc);
    }
    return visited.size();
}

int main() {
    cout << "Number of unique houses visited: " << housesVisited() << endl;
    return 0;
}