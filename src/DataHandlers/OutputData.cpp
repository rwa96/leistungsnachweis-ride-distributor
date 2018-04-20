#include <fstream>
#include "OutputData.hpp"

void OutputData::writeToFile(const std::string path, const unsigned fleetSize) const {
    std::fstream outFile;
    outFile.exceptions(std::fstream::failbit | std::fstream::badbit);
    std::vector<std::list<unsigned>> data = createDataStructure(shared_from_this(),
                                            fleetSize);

    outFile.open(path, std::fstream::out);

    for(auto car : data) {
        outFile << car.size() << ' ';

        for(auto ride : car) {
            outFile << ride << ' ';
        }

        outFile << std::endl;
    }
}

std::vector<std::list<unsigned>> OutputData::createDataStructure(
std::shared_ptr<const OutputData> start, const unsigned fleetSize) const {
    std::vector<std::list<unsigned>> data(fleetSize, std::list<unsigned>());
    std::shared_ptr<const OutputData> current_node(start);

    while(current_node) {
        for(unsigned row = 0; row < current_node->value->getDims()[1]; ++row) {
            data[(*current_node->value)(row, 0)].push_front((*current_node->value)(row, 1));
        }

        current_node = current_node->parent;
    }

    return data;
}
