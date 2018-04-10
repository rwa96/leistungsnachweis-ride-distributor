#include <iostream>
#include <fstream>
#include "InputData.hpp"

int main(int argc, char* argv[]){
	if (argc == 2) {
		try {
			InputData inputData(argv[1]);
			std::cout << inputData.str();
		}
		catch (const std::fstream::failure e) {
			std::cerr << e.what() << "(Invalid file or path)" << std::endl;
			return 1;
		}
	}
	else {
		std::cerr << "No path argument set" << std::endl;
		return 1;
	}

	return 0;
}
