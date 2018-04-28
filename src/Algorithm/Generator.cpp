#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>
#include <set>
#include "Generator.hpp"

void Generator::createSearchSpace(Tensor<int>& finishTimes, Tensor<int>& finishPoints,
                                  std::vector<int>& unassigned, std::unique_ptr<Types::CarData>& cars) {
    // For each unassigned ride, calculate times and points for all cars
    auto ride = unassigned.begin();

    for(unsigned uIndex = 0; uIndex < unassigned.size(); ++uIndex, ++ride) {

        // distance of current ride
        int rideDistance = inputData.distances(*ride);
        // earliest possible start of current ride
        int earliestStart = inputData.startT(*ride);
        // latest possible finish of current ride
        int latestFinish = inputData.endT(*ride);

        for(unsigned car = 0; car < inputData.fleetSize; ++car) {

            // current time of the car
            int carTime = cars->t(car);
            // distance to ride starting point
            int ariveDistance = std::abs(cars->x(car) - inputData.startX(*ride)) +
                                std::abs(cars->y(car) - inputData.startY(*ride));
            // point in time when the ride can start (car arrived)
            int startTime = std::max(carTime + ariveDistance, earliestStart);

            finishTimes(car, uIndex) = startTime + rideDistance;
            finishPoints(car, uIndex) = cars->p(car);

            // ride ended in time (points gained)
            if(latestFinish >= finishTimes(car, uIndex)) {
                finishPoints(car, uIndex) += rideDistance;
            }

            // ride started in time (bonus gained)
            if(earliestStart == startTime) {
                finishPoints(car, uIndex) += inputData.bonus;
            }
        }
    }
}

void Generator::selectFromSearchSpace(Types::Choices& output,
                                      std::shared_ptr<SearchGraphNode>& prevNode, Tensor<int>& finishTimes,
                                      Tensor<int>& finishPoints, std::vector<int>& unassigned,
                                      std::unique_ptr<Types::CarData>& cars) {
    // set up data structure to permutate though finishTimes and finishTimes
    std::set<int> unassignedIndices(unassigned.begin(), unassigned.end());
    auto rng = std::default_random_engine();
    unsigned nAssignments = std::min(inputData.fleetSize,
                                     static_cast<unsigned>(unassigned.size()));
    std::vector<int> carIndices(inputData.fleetSize);
    std::iota(carIndices.begin(), carIndices.end(), 0);
    std::vector<int> rideIndices(unassigned.size());
    std::iota(rideIndices.begin(), rideIndices.end(), 0);

    // try a specified amount of times to find good random permutations
    for(unsigned tryIndex = 0; tryIndex < nTries; ++tryIndex) {
        // create random permutation
        std::shuffle(carIndices.begin(), carIndices.end(), rng);
        std::shuffle(rideIndices.begin(), rideIndices.end(), rng);

        // create choice (representation of the results of this random permutation)
        std::unique_ptr<Tensor<unsigned>> searchNodeValue(new Tensor<unsigned>({ nAssignments, 2 }));
        std::unique_ptr<Types::Choice> choice(new Types::Choice(*cars));

        // setup data structure to evaluate this permutation and create the choice
        auto carItr = carIndices.begin();
        auto rideItr = rideIndices.begin();
        std::set<int> newUnassigned(unassigned.begin(), unassigned.end());
        float timeSum = 0;
        float pointSum = 0;
        int car, uIndex, ride;

        // iterate over the random permutations
        for(unsigned assignIndex = 0; assignIndex < nAssignments; ++assignIndex) {
            car = *(carItr++);
            uIndex = *(rideItr++);
            ride = unassigned[uIndex];
            newUnassigned.erase(ride);

            choice->cars.x(car) = inputData.endX(ride);
            choice->cars.y(car) = inputData.endY(ride);
            choice->cars.t(car) += finishTimes(car, uIndex);
            choice->cars.p(car) += finishPoints(car, uIndex);

            (*searchNodeValue)(assignIndex, 0) = car;
            (*searchNodeValue)(assignIndex, 1) = ride;

            timeSum += choice->cars.t(car);
            pointSum += choice->cars.p(car);
        }

        // write back results
        choice->score = inputData.maxTime - timeSum / nAssignments + pointSum / nAssignments;
        choice->unassigned.insert(choice->unassigned.begin(), newUnassigned.begin(),
                                  newUnassigned.end());
        choice->searchGraphNode = std::shared_ptr<SearchGraphNode>(new SearchGraphNode(prevNode,
                                  searchNodeValue));
        output.push_back(std::move(choice));
    }
}

void Generator::generate(Types::Choices& output,
                         std::shared_ptr<SearchGraphNode>& prevNode, std::vector<int>& unassigned,
                         std::unique_ptr<Types::CarData> cars) {

    // Time after each car was assigned to each unassigned ride (2D matrix)
    Tensor<int> finishTimes({ inputData.fleetSize, static_cast<unsigned>(unassigned.size()) });
    // Points after each car was assigned to each unassigned ride (2D matrix)
    Tensor<int> finishPoints({ inputData.fleetSize, static_cast<unsigned>(unassigned.size()) });
    createSearchSpace(finishTimes, finishPoints, unassigned, cars);
    selectFromSearchSpace(output, prevNode, finishTimes, finishPoints, unassigned, cars);

};
