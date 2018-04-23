#include <iostream>
#include <fstream>
#include <memory>
#include <numeric>
#include "InputData.hpp"
#include "Generator.hpp"
#include "Aggregator.hpp"

int main(int argc, char* argv[]) {
    if(argc == 2) {
        try {
			// InputData + Generator
			std::shared_ptr<InputData> inputData = InputData::genFromFile(argv[1]);
			Generator generator(*inputData, 4, 2);
			Types::Choices choices;
			std::vector<int> unassigned(inputData->nRides);
			std::iota(unassigned.begin(), unassigned.end(), 0);
			std::unique_ptr<Types::CarData> cars(new Types::CarData(inputData->fleetSize));
			generator.generate(choices, unassigned, std::move(cars));

			for (std::unique_ptr<Types::Choice>& choice : choices) {
				std::cout << "Choice:" << std::endl;
				std::cout << '\t' << "x: " << choice->cars.x.str();
				std::cout << '\t' << "y: " << choice->cars.y.str();
				std::cout << '\t' << "t: " << choice->cars.t.str();
				std::cout << '\t' << "p: " << choice->cars.p.str();
				std::cout << '\t' << "Score: " << choice->score << std::endl;
			}


			// Aggregator
			Aggregator aggregator(*inputData, 2);
			aggregator.aggregate(choices);

			std::cout << '\n' << "Picked beamsize best choices." << std::endl;
			for (std::unique_ptr<Types::Choice>& choice : choices) {
				std::cout << "Score: " << choice->score << std::endl;
			}

        } catch(const std::fstream::failure e) {
            std::cerr << e.what() << "(Invalid file or path)" << std::endl;
            return 1;
        }
    } else {
        std::cerr << "No path argument set" << std::endl;
        return 1;
    }

    return 0;
}
