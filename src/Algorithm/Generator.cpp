#include <cmath>
#include "Generator.hpp"

Types::Choices Generator::generate(InputData& inputData, std::unique_ptr<Tensor<int>> unassigned, std::unique_ptr<Types::CarData> cars){
	
	std::unique_ptr<Tensor<int>> result(new Tensor<int>({ inputData.fleetSize, unassigned->getSize() }));

	for (unsigned uIndex = 0, ride = (*unassigned)(0); uIndex < unassigned->getSize(); ride = (*unassigned)(++uIndex)) {

		int rideDistance = inputData.distances(ride);
		int startTime = inputData.startT(ride);

		for (unsigned car = 0; car < inputData.fleetSize; ++car) {

			int carTime = cars->t(car);
			int ariveDistance = std::abs(cars->x(car) - inputData.startX(ride)) + std::abs(cars->y(car) - inputData.startY(ride));
			(*result)(car, uIndex) = rideDistance + std::max(carTime + ariveDistance, startTime);
		}
	}

	return {};
}