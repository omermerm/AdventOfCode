#include <iostream>
#include <fstream>

int count_parenthesis() {
    std::ifstream input_file ("1A-input.txt");
    int pos = 0;
    char c;
    while(input_file){
        c = input_file.get();
        if (c == '(') {pos++;}
        else if (c == ')') {pos--;}
        else {}
    }
    input_file.close();
    return pos;
}

int main() {
    std::cout << count_parenthesis();
    return 0;
}