#include <iostream>
#include <fstream>
#include "InputData.hpp"

int main(int argc, char* argv[]) {
    if(argc == 2) {
        try {
            std::cout << InputData::genFromFile(argv[1])->str();
        } catch(const std::fstream::failure e) {
            std::cerr << e.what() << "(Invalid file or path)" << std::endl;
            return 1;
        }
    } else {
        std::cerr << "No path argument set" << std::endl;
        return 1;
    }

    return 0;
}
