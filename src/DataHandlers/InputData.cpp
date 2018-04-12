#include <sstream>
#include "InputData.hpp"

InputData::InputData(const std::string path){
	std::fstream inFile;
	inFile.exceptions(std::fstream::failbit | std::fstream::badbit);

	inFile.open(path, std::fstream::in);
	inFile >> rows >> cols >> fleetSize >> nRides >> bonus >> maxTime;

    startX = Tensor<int>({nRides});
    startY = Tensor<int>({nRides});
    endX = Tensor<int>({nRides});
    endY = Tensor<int>({nRides});
    startT = Tensor<int>({nRides});
    endT = Tensor<int>({nRides});
    distances = Tensor<int>({nRides});

	for (unsigned short i = 0; i < nRides; i++) {
		inFile >> startX(i) >> startY(i);
        inFile >> endX(i) >> endY(i);
        inFile >> startT(i) >> endT(i);
        distances(i) = abs(startX(i) - endX(i)) + abs(startY(i) - endY(i));
	}
};

std::string InputData::str() const {
	std::ostringstream result;

	result << "number of rides: " << nRides << std::endl;
	result << "map: (" << rows << ", " << cols << ")" << std::endl;
	result << "number of cars: " << fleetSize << std::endl;
	result << "bonus: " << bonus << std::endl;
	result << "simulation steps: " << maxTime << std::endl;

	return result.str();
};
