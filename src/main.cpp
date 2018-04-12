#include <iostream>
#include <fstream>
#include <cmath>
#include "InputData.hpp"

Tensor<int> getChoices(InputData& inputData,
                       Tensor<int>& unassigned,
                       Tensor<int>& carX,
                       Tensor<int>& carY,
                       Tensor<int>& carT,
                       Tensor<int>& carP)
{
    Tensor<int> result({inputData.fleetSize, unassigned.getSize()});
    for(unsigned uIndex = 0, ride = unassigned(0); uIndex < unassigned.getSize(); ride = unassigned(++uIndex)){

        int rideDistance = inputData.distances(ride);
        int startTime = inputData.startT(ride);

        for(unsigned car = 0; car < inputData.fleetSize; ++car){

            int carTime = carT(car);
            int ariveDistance = std::abs(carX(car) - inputData.startX(ride)) + std::abs(carY(car) - inputData.startY(ride));
            result(car, uIndex) = rideDistance + std::max(carTime + ariveDistance, startTime);
        }
    }

    return result;
}

int main(int argc, char* argv[]){
	if (argc == 2) {
		try {
			InputData inputData(argv[1]);
            Tensor<int> unassigned({inputData.nRides});
            for(unsigned i = 0; i < inputData.nRides; ++i){
                unassigned(i) = i;
            }
            std::cout << unassigned.str();
            Tensor<int> carX({inputData.fleetSize}), carY({inputData.fleetSize}), carT({inputData.fleetSize}), carP({inputData.fleetSize});
            for(unsigned i = 0; i < inputData.fleetSize; ++i){
                carX(i) = 0; carY(i) = 0; carT(i) = 0; carP(i) = 0;
            }
            std::cout << getChoices(inputData, unassigned, carX, carY, carT, carP).str();
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
