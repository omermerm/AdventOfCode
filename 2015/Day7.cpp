#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

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

vector<string> read_file(string filename) {
    vector<string> lines{};
    ifstream file (filename);
    while(file.good()) {
        string line;
        getline(file, line);
        lines.push_back(line);
    }
    file.close();
    return lines;
}

map<string, string> parse_instruction(string instruction) {
    map<string, string> inst_map;
    vector<string> words = split(instruction, " ");

    if (words[1] == "->") {
        inst_map["operation"] = "PUT";
        inst_map["input A"] = words[0];
        inst_map["output"] = words[2];
    } else if (words[2] == "->") {
        inst_map["operation"] = words[0];
        inst_map["input A"] = words[1];
        inst_map["output"] = words[3];
    } else if (words [3] == "->") {
        inst_map["operation"] = words[1];
        inst_map["input A"] = words[0];
        inst_map["input B"] = words[2];
        inst_map["output"] = words[4];
    } else {
        throw invalid_argument("non-parsable instruction");
    }
    return inst_map;
}

bool in_map(map<string, unsigned short>* m, string value) {
    return (*m).find(value) != (*m).end();
}

unsigned short emulateCircuit(string filename, bool second_part=false, unsigned short b_value=0) {
    vector<string> input_lines = read_file(filename);
    map<string, map<string, string>> components{};
    for (int i = 0; i < input_lines.size(); i++){
        auto comp = parse_instruction(input_lines[i]);
        components[comp["output"]] = comp;
    }

    map<string, vector<string>> digraph{};
    for (auto & keyval : components) {
        string out = keyval.first;
        map<string, string> component = keyval.second;
        digraph[component["input A"]].push_back(out);
        if (!(component["operation"] == "PUT" || component["operation"] == "NOT")) {
            digraph[component["input B"]].push_back(out);
        }
    }


    vector<string> stack{};
    map<string, unsigned short> vals{};
    for (auto & node : digraph){
        try {
            int val = stoi(node.first);
            vals[node.first] = val;
            for (auto & child : digraph[node.first]) {
                    stack.push_back(child);
                }
        } catch (const exception & e) {
            /* do nothing */
        }
    }

    //override wire b with given value if doing second part
    if (second_part) {
        vals["b"] = b_value;
        for (auto & child : digraph["b"]) {
            stack.push_back(child);
        }
    }

    while(stack.size() > 0) {
        string node = stack.back();
        stack.pop_back();
        if ( !in_map(&vals, node) && in_map(&vals, components[node]["input A"]) ) {
            bool continue_dfs = true;
            unsigned short input_a = vals[components[node]["input A"]];
            string op = components[node]["operation"];
            if (op == "NOT") {
                vals[node] = ~input_a;
            } else if (op == "PUT"){
                vals[node] = input_a;
            } else if (in_map(&vals, components[node]["input B"])) {
                unsigned short input_b = vals[components[node]["input B"]];
                if (op == "AND") {
                    vals[node] = input_a & input_b;
                } else if (op == "OR") {
                    vals[node] = input_a | input_b;
                } else if (op == "LSHIFT") {
                    vals[node] = input_a << input_b;
                } else if (op == "RSHIFT") {
                    vals[node] = input_a >> input_b;
                } else { throw invalid_argument("bad command");}
            } else{ /*not all inputs have been initialized yet*/
                continue_dfs = false;
            }

            if (continue_dfs) {
                for (auto & child : digraph[node]) {
                    stack.push_back(child);
                }
            }
        }
    }

    return vals["a"];
}

int main() {
    unsigned short a_signal = emulateCircuit("Day7-input.txt");
    cout << "Signal on wire `a`: " << a_signal << endl;
    cout << "Signal on wire `a`: " << emulateCircuit("Day7-input.txt", true, a_signal) << endl;
    return 0;
}