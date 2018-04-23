#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include "Types.hpp"
#include "InputData.hpp"

class Aggregator {
public:

	Aggregator(InputData& inputData, unsigned beamSize) :
		inputData(inputData), beamSize(beamSize) {};

    void aggregate(Types::Choices& choices);

private:

	static bool sortByScore(const std::unique_ptr<Types::Choice>& lhs, const std::unique_ptr<Types::Choice>& rhs);

    InputData& inputData;
    unsigned beamSize;

};

#endif // AGGREGATOR_H
