#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>
#include <vector>
#include "Generator.hpp"

Types::Choices Generator::generate(std::unique_ptr<Tensor<int>> unassigned, std::unique_ptr<Types::CarData> cars){

	Tensor<int> finishTimes({ inputData.fleetSize, unassigned->getSize() });
	Tensor<int> finishPoints({ inputData.fleetSize, unassigned->getSize() });

	/*auto rng = std::default_random_engine();
	std::vector<int> indices(std::max(inputData.fleetSize, unassigned->getSize()));
	std::iota(indices.begin(), indices.end(), 0);
	std::shuffle(indices.begin(), indices.end(), rng);
	std::set<std::pair<int, int>> uniqueIndices();

	unsigned assingTableSize = std::min(inputData.fleetSize, unassigned->getSize());

	Tensor<int> selections({ nTries, assingTableSize, 2 });
	for (unsigned tryIndex = 0; tryIndex < nTries; ++tryIndex) {
		auto sIndex = indices.begin();
		for (unsigned assignIndex = 0; assignIndex < assingTableSize; ++assignIndex) {
			int car = (*sIndex) % inputData.fleetSize;
			int ride = (*sIndex) % unassigned->getSize();
			selections(tryIndex, assignIndex, 0) = car;
			selections(tryIndex, assignIndex, 1) = ride;

		}
	}*/


	for (unsigned uIndex = 0, ride = (*unassigned)(0); uIndex < unassigned->getSize(); ride = (*unassigned)(++uIndex)) {

		int rideDistance = inputData.distances(ride);
		int earliestStart = inputData.startT(ride);
		int latestFinish = inputData.endT(ride);

		for (unsigned car = 0; car < inputData.fleetSize; ++car) {

			int carTime = cars->t(car);
			int ariveDistance = std::abs(cars->x(car) - inputData.startX(ride)) + std::abs(cars->y(car) - inputData.startY(ride));
			int startTime = std::max(carTime + ariveDistance, earliestStart);

			finishTimes(car, uIndex) = startTime + rideDistance;
			/*if (finishTimes(car, uIndex) > inputData.maxTime) {
				finishTimes(car, uIndex) = inputData.maxTime;
			}*/

			finishPoints(car, uIndex) = cars->p(car);
			if (latestFinish >= finishTimes(car, uIndex)) {
				finishPoints(car, uIndex) += rideDistance;
			}
			if (earliestStart == startTime) {
				finishPoints(car, uIndex) += inputData.bonus;
			}
		}
	}

	auto rng = std::default_random_engine();
	unsigned assingTableSize = std::min(inputData.fleetSize, unassigned->getSize());
	std::vector<int> carIndices(inputData.fleetSize);
	std::iota(carIndices.begin(), carIndices.end(), 0);
	std::vector<int> rideIndices(unassigned->getSize());
	std::iota(rideIndices.begin(), rideIndices.end(), 0);
	for (unsigned tryIndex = 0; tryIndex < nTries; ++tryIndex) {
		std::shuffle(carIndices.begin(), carIndices.end(), rng);
		std::shuffle(rideIndices.begin(), rideIndices.end(), rng);

		//std::unique_ptr<Types::Choice> current()

		for (unsigned assignIndex = 0; assignIndex < assingTableSize; ++assignIndex) {

		}
	}

	return {};
};
