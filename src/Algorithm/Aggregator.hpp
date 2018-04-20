#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include "Types.hpp"

class Aggregator {
public:

    Aggregator(InputData& inputData, unsigned beamSize) :
        inputData(inputData), beamSize(beamSize);

    void aggregate(Types::Choices & choices);

private:

    InputData & inputData;
    unsigned beamSize;

};

#endif // AGGREGATOR_H
