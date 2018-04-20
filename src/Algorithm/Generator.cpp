#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>
#include <set>
#include "Generator.hpp"

void Generator::generate(Types::Choices& output, std::vector<int>& unassigned, std::unique_ptr<Types::CarData> cars){

	Tensor<int> finishTimes({ inputData.fleetSize, static_cast<unsigned>(unassigned.size()) });
	Tensor<int> finishPoints({ inputData.fleetSize, static_cast<unsigned>(unassigned.size()) });

	auto ride = unassigned.begin();
	for (unsigned uIndex = 0; uIndex < unassigned.size(); ++uIndex, ++ride) {

		int rideDistance = inputData.distances(*ride);
		int earliestStart = inputData.startT(*ride);
		int latestFinish = inputData.endT(*ride);

		for (unsigned car = 0; car < inputData.fleetSize; ++car) {

			int carTime = cars->t(car);
			int ariveDistance = std::abs(cars->x(car) - inputData.startX(*ride)) + std::abs(cars->y(car) - inputData.startY(*ride));
			int startTime = std::max(carTime + ariveDistance, earliestStart);

			finishTimes(car, uIndex) = startTime + rideDistance;
			finishPoints(car, uIndex) = cars->p(car);
			if (latestFinish >= finishTimes(car, uIndex)) {
				finishPoints(car, uIndex) += rideDistance;
			}
			if (earliestStart == startTime) {
				finishPoints(car, uIndex) += inputData.bonus;
			}
		}
	}

	std::set<int> unassignedIndices(unassigned.begin(), unassigned.end());
	auto rng = std::default_random_engine();
	unsigned nAssignments = std::min(inputData.fleetSize, static_cast<unsigned>(unassigned.size()));
	std::vector<int> carIndices(inputData.fleetSize);
	std::iota(carIndices.begin(), carIndices.end(), 0);
	std::vector<int> rideIndices(unassigned.size());
	std::iota(rideIndices.begin(), rideIndices.end(), 0);
	for (unsigned tryIndex = 0; tryIndex < nTries; ++tryIndex) {
		std::shuffle(carIndices.begin(), carIndices.end(), rng);
		std::shuffle(rideIndices.begin(), rideIndices.end(), rng);

        std::unique_ptr<Types::Choice> choice(new Types::Choice(*cars));

        auto carItr = carIndices.begin();
        auto rideItr = rideIndices.begin();
		std::set<int> newUnassigned(unassigned.begin(), unassigned.end());
		float timeSum = 0;
		float pointSum = 0;
		int car, uIndex, ride;
		for (unsigned assignIndex = 0; assignIndex < nAssignments; ++assignIndex) {
            car = *(carItr++); uIndex = *(rideItr++); ride = unassigned[uIndex];
			newUnassigned.erase(ride);

            choice->cars.x(car) = inputData.endX(ride);
            choice->cars.y(car) = inputData.endY(ride);
            choice->cars.t(car) += finishTimes(car, uIndex);
            choice->cars.p(car) += finishPoints(car, uIndex);

			timeSum += choice->cars.t(car);
			pointSum += choice->cars.p(car);
		}
		choice->score = inputData.maxTime - timeSum / nAssignments + pointSum / nAssignments;
		choice->unassigned.insert(choice->unassigned.begin(), newUnassigned.begin(), newUnassigned.end());
		output.push_back(std::move(choice));
	}
};
