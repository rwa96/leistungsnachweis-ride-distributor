#include <iostream>
#include <fstream>
#include "InputData.hpp"

int main(){
	try {
		InputData inputData("resources/d_metropolis.in");
		std::cout << inputData.str();
	}
	catch (const std::fstream::failure e) {
		std::cerr << e.what();
		return 1;
	}

	return 0;
}
