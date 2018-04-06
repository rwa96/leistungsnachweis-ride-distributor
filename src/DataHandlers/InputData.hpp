#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <fstream>
#include <string>
#include "Tensor.hpp"


struct InputData{

    InputData(const std::string path);
    std::string str() const;

    unsigned rows, cols, fleetSize, nRides, bonus, maxTime;
    Tensor startX, startY, endX, endY, startT, endT, distances;

};

#endif // INPUTDATA_H
