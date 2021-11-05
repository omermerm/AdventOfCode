#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool is_nice(string s) {
    bool no_forbidden = true, double_letter = false;
    int vowels = 0;
    if (s.find("ab") != string::npos ||
        s.find("cd") != string::npos ||
        s.find("pq") != string::npos ||
        s.find("xy") != string::npos) {
        no_forbidden = false;
        }
    char prev = '?'; // it's given that ? does not appear in the input strings
    string vowel_str = "aeiou";
    if (no_forbidden){
        for (int i=0; i < s.size() && (!double_letter || vowels < 3); i++) {
            if (vowels < 3 && vowel_str.find(s[i]) != string::npos){ vowels += 1; }
            if (s[i] == prev) { double_letter = true; }
            prev = s[i];
    }}
    return no_forbidden && vowels >= 3 && double_letter;
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