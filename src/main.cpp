#include <iostream>
#include <fstream>
#include "InputData.hpp"

int main(){
	try {
		InputData inputData("../../resources/a_example.in");
		std::cout << inputData.str();
	}
	catch (const std::fstream::failure e) {
		std::cerr << e.what();
		return 1;
	}

	return 0;
}
