#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool is_nice(string s) {
    bool repeat_with_space = false, repeat_pair = false;

    for (int i=s.size() - 2; i > 0 && (!repeat_with_space || !repeat_pair); i--) {
        if (!repeat_with_space){ repeat_with_space = (s[i+1] == s[i-1]); }
        if (!repeat_pair) { repeat_pair = (s.find(s.substr(i, 2)) < i-1); } // the pair of chars is found in a non-overlapping way
    }
    return repeat_with_space && repeat_pair;
}

int numNiceStrings() {
    ifstream input_file ("Day5-input.txt");
    int nice_counter = 0;
    while(input_file.good()){
        string str;
        getline(input_file, str);
        if (is_nice(str)) { nice_counter += 1;}
    }
    input_file.close();
    return nice_counter;
}

int main() {
    cout << "Number of nice string: " << numNiceStrings() << endl;
    return 0;
}