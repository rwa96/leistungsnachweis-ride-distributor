#include <cmath>
#include <numeric>
#include <algorithm>
#include <set>
#include "Generator.hpp"
#include "RLAPSolverHungarian.hpp"

int Generator::createSearchSpace(Tensor<int>& finishTimes, Tensor<int>& finishPoints,
                                  std::vector<int>& unassigned, std::unique_ptr<Types::CarData>& cars)
{
    int maxValue = 0;

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

            if(maxValue < finishPoints(car, uIndex)){
                maxValue = finishPoints(car, uIndex);
            }
        }
    }

    return maxValue;
}

void Generator::selectFromSearchSpace(Types::Choices& output,
                                      std::shared_ptr<SearchGraphNode>& prevNode, Tensor<int>& finishTimes,
                                      Tensor<int>& finishPoints, std::vector<int>& unassigned,
                                      int maxValue, std::unique_ptr<Types::CarData>& cars)
{
    // no possible choices left
    const unsigned nAssignments = std::min(inputData.fleetSize, static_cast<unsigned>(unassigned.size()));
    if(nAssignments == 0) { return; }

    // solve RLAP to maximize gained points
    RLAPSolverHungarian solver(finishPoints, maxValue);
    std::unique_ptr<Tensor<unsigned>> searchNodeValue(new Tensor<unsigned>({ nAssignments, 2 }));
    solver.solve(*searchNodeValue);

    // init data structure for result
    std::unique_ptr<Types::Choice> choice(new Types::Choice(*cars));
    std::set<int> newUnassigned(unassigned.begin(), unassigned.end());

    float timeSum = 0;
    float pointSum = 0;
    for(unsigned i = 0; i < nAssignments; ++i){
        const int car = (*searchNodeValue)(i, 0);
        const int uIndex = (*searchNodeValue)(i, 1);
        const int ride = unassigned[uIndex];
        newUnassigned.erase(ride);

        choice->cars.x(car) = inputData.endX(ride);
        choice->cars.y(car) = inputData.endY(ride);
        choice->cars.t(car) = finishTimes(car, uIndex);
        choice->cars.p(car) = finishPoints(car, uIndex);

        (*searchNodeValue)(i, 1) = ride;

        timeSum += choice->cars.t(car);
        pointSum += choice->cars.p(car);
    }

    // write back results
    float timeAvg = timeSum / nAssignments;

    if(timeAvg > inputData.maxTime) {
        timeAvg = inputData.maxTime;
    }

    choice->score = inputData.maxTime - timeAvg + pointSum / nAssignments;
    choice->unassigned.insert(choice->unassigned.begin(), newUnassigned.begin(),
                              newUnassigned.end());
    choice->searchGraphNode = std::shared_ptr<SearchGraphNode>(new SearchGraphNode(prevNode,
                              searchNodeValue));
    output.push_back(std::move(choice));
}

void Generator::generate(Types::Choices& output,
                         std::shared_ptr<SearchGraphNode>& prevNode, std::vector<int>& unassigned,
                         std::unique_ptr<Types::CarData> cars) {

    // Time after each car was assigned to each unassigned ride (2D matrix)
    Tensor<int> finishTimes({ inputData.fleetSize, static_cast<unsigned>(unassigned.size()) });
    // Points after each car was assigned to each unassigned ride (2D matrix)
    Tensor<int> finishPoints({ inputData.fleetSize, static_cast<unsigned>(unassigned.size()) });
    int maxValue = createSearchSpace(finishTimes, finishPoints, unassigned, cars);
    selectFromSearchSpace(output, prevNode, finishTimes, finishPoints, unassigned, maxValue, cars);

};
