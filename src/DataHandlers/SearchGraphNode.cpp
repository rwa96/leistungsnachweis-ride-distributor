#include <fstream>
#include "SearchGraphNode.hpp"

void SearchGraphNode::writeToFile(const std::string path,
                                  const unsigned fleetSize) const {
    std::fstream outFile;
    outFile.exceptions(std::fstream::failbit | std::fstream::badbit);
    std::vector<std::list<unsigned>> data = createDataStructure(fleetSize);

    outFile.open(path, std::fstream::out);

    for(auto car : data) {
		outFile << car.size();
		
		if (car.size() > 0) {
			outFile << ' ';
		}

		unsigned rideCount = 0;
        for(auto ride : car) {
			outFile << ride;

			if (rideCount < car.size() - 1) {
				outFile << ' ';
			}
			++rideCount;
        }

		outFile << std::endl;
    }
}

std::vector<std::list<unsigned>> SearchGraphNode::createDataStructure(
const unsigned fleetSize) const {

    std::vector<std::list<unsigned>> data(fleetSize, std::list<unsigned>());

    for(unsigned row = 0; value->getSize() > 0 && row < value->getDims()[0]; ++row) {
        data[(*value)(row, 0)].push_front((*value)(row, 1));
    }

    std::shared_ptr<const SearchGraphNode> current_node = parent;

    while(current_node) {
        for(unsigned row = 0; current_node->value->getSize() > 0 &&
            row < current_node->value->getDims()[0]; ++row) {
            data[(*current_node->value)(row, 0)].push_front((*current_node->value)(row, 1));
        }

        current_node = current_node->parent;
    }

    return data;
}
