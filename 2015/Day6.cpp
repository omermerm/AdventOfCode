#include <iostream>
#include <fstream>
#include <string>
#include <functional>

using namespace std;

int numLightsOn(bool brightness) {
    static int grid[1000][1000];
    for (int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            grid[i][j] = 0;
    }}
    ifstream input_file ("Day6-input.txt");
    while(input_file.good()) {
        string instruction;
        getline(input_file, instruction, ' ');
        // discard the turn in "turn on" and "turn off"
        if (instruction == "turn") { getline(input_file, instruction, ' '); }
        function<int (int)> apply_instruction;
        switch (instruction[1])
        {
        // case "on"
        case 'n':
            if (brightness) {
                apply_instruction = [](int light) { return light + 1; };
            } else {
                apply_instruction = [](int light) { return 1; };
            }
            break;
        // case "off"
        case 'f':
            if (brightness) {
                apply_instruction = [](int light) { return max(light - 1, 0); };
            } else {
                apply_instruction = [](int light) { return 0; };
            }
            break;
        // case "toggle"
        case 'o':
            if (brightness) {
                apply_instruction = [](int light) { return light + 2; };
            } else {
                apply_instruction = [](int light) { return !light; };
            }
            break;
        // default - do nothing
        default:
            apply_instruction = [](int light) { return light; };
            break;
        }

        // read coordinates
        string temp;
        getline(input_file, temp, ',');
        int left = stoi(temp);
        getline(input_file, temp, ' ');
        int top = stoi(temp);
        getline(input_file, temp, ' '); // discard "through"
        getline(input_file, temp, ',');
        int right = stoi(temp);
        getline(input_file, temp);
        int bottom = stoi(temp);
        
        for (int i = top; i <= bottom; i++){
            for (int j = left; j <= right; j++){
                grid[i][j] = apply_instruction(grid[i][j]);
        }}
    }
    int light_sum = 0;
    for (int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            light_sum += grid[i][j];
    }}
    return light_sum;
}

int main() {
    cout << "On/Off - Number of lights on at the end: " << numLightsOn(false) << std::endl;
    cout << "Brightness - Total brightness at the end: " << numLightsOn(true) << std::endl;
    return 0;
}