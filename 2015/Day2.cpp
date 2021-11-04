#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

int * howMuchWrapping() {
    std::ifstream input_file ("Day2-input.txt");
    int acc_paper = 0;
    int acc_ribbon = 0;
    std::string dimstr;
    while(input_file.good()) {
        std::getline(input_file, dimstr);
        std::stringstream dimstream (dimstr);
        std::string dim;
        int dims[3];
        for (int i = 0; std::getline(dimstream, dim, 'x'); i++){
            dims[i] = std::stoi(dim);
        }
        int faces[] = {dims[0]*dims[1], dims[0]*dims[2], dims[1]*dims[2]};
        int volume = dims[0]*dims[1]*dims[2];
        int dims_sum = std::accumulate(dims, dims+3, 0);
        int max_dim = *std::max_element(dims, dims+3);
        int faces_sum = std::accumulate(faces, faces+3, 0);
        int min_face = *std::min_element(faces, faces+3);
        acc_paper += min_face + 2*faces_sum;
        acc_ribbon += volume + 2*(dims_sum - max_dim);
    }
    static int ans[] = {acc_paper, acc_ribbon};
    return ans;
}

int main() {
    int * wrapping = howMuchWrapping();
    std::cout << "Wrapping paper needed: " << wrapping[0] << std::endl;
    std::cout << "Feet of ribbon needed: " << wrapping[1] << std::endl;
    return 0;
}