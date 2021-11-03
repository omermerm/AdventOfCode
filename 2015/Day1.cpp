#include <iostream>
#include <fstream>

int * count_parenthesis() {
    std::ifstream input_file ("1A-input.txt");
    int pos = 0;
    int floor = 0;
    int first_basement = 0;
    char c;
    while(input_file){
        c = input_file.get();
        pos++;
        if (c == '(') {floor++;}
        else if (c == ')') {floor--;}
        else {}

        if (floor < 0 & first_basement == 0) {first_basement = pos;}
    }
    input_file.close();
    std::cout << pos << floor << "\n" ;
    static int ans[2] = {floor, first_basement};
    return ans;
}

int main() {
    int* vals = count_parenthesis();
    std::cout << "final floor: " << vals[0] << std::endl;
    std::cout << "first basement entry: " << vals[1] << std::endl;
    return 0;
}