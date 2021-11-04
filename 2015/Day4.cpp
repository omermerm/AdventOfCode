#include <iostream>
#include <fstream>
#include <string>
#include "md5.cpp"

using namespace std;

int firstGoodHash() {
    ifstream input_file ("Day4-input.txt");
    string key;
    getline(input_file, key);
    input_file.close();

    int ans = -1;
    int n = 0;
    int max = 10000000; // force-terminate loop
    string wanted = "00000"; //Change this to "000000" for second part of puzzle
    while(n < max) {
        string hash_start = md5(key + to_string(n)).substr(0,wanted.size());
        if (hash_start == wanted){
            ans = n;
            break;
        }
        n += 1;
    }
    return ans;

}

int main() {
    cout << "First number whose hash with the key begins with 00000: " << firstGoodHash() << endl;
    return 0;
}