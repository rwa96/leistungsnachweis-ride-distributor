#include <sstream>
#include "InputData.hpp"

std::shared_ptr<InputData> InputData::genFromFile(const std::string path) {
    std::fstream inFile;
    inFile.exceptions(std::fstream::failbit | std::fstream::badbit);

    inFile.open(path, std::fstream::in);
    unsigned rows, cols, fleetSize, nRides, bonus, maxTime;
    inFile >> rows >> cols >> fleetSize >> nRides >> bonus >> maxTime;

    return std::shared_ptr<InputData>(new InputData(rows, cols, fleetSize, nRides, bonus,
                                      maxTime, inFile));
};

InputData::InputData(
    const unsigned rows,
    const unsigned cols,
    const unsigned fleetSize,
    const unsigned nRides,
    const unsigned bonus,
    const unsigned maxTime,
    std::fstream& inFile
):
    rows(rows), cols(cols), fleetSize(fleetSize), nRides(nRides), bonus(bonus),
    maxTime(maxTime), startX({nRides}), startY({nRides}), endX({nRides}),
endY({nRides}), startT({nRides}), endT({nRides}), distances({nRides}) {
    for(unsigned short i = 0; i < nRides; i++) {
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
