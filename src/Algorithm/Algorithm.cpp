#include <numeric>
#include <cmath>
#include "Algorithm.hpp"

#ifndef NDEBUG
    #include <iostream>
    #define DBG_PRINT_CHOICE(choice) std::cout << "Choice:" << std::endl; \
        DBG_PRINT_1D_TENSOR("x", choice->cars.x); \
        DBG_PRINT_1D_TENSOR("y", choice->cars.y); \
        DBG_PRINT_1D_TENSOR("t", choice->cars.t); \
        DBG_PRINT_1D_TENSOR("p", choice->cars.p); \
        std::cout << "Score: " << choice->score << std::endl
#else
    #define DBG_PRINT_CHOICE(_)
#endif

bool Algorithm::checkCarDataValid(Types::CarData carData, unsigned T) {
    bool result = true;

    for(int i = 0; i < carData.t.getSize(); i++) {
        if(carData.t(i) > T) {
            result = false;
            break;
        }
    }

    return result;
}

// TODO Improve documentation
void Algorithm::run() {

    // First Generator run
    Types::Choices choices;
    std::vector<int> unassigned(inputData.nRides);
    std::iota(unassigned.begin(), unassigned.end(), 0);
    std::unique_ptr<Types::CarData> cars(new Types::CarData(inputData.fleetSize));
    std::shared_ptr<SearchGraphNode> parentNode;

    generator.generate(choices, parentNode, unassigned, std::move(cars));

    // First Aggregator run
    aggregator.aggregate(choices);
    std::cout << std::round((inputData.nRides - choices.front()->unassigned.size()) * 100.0 /
                            inputData.nRides) << "% of rides are assigned." << std::endl;

    // Main while loop, which finds best choice.
    // Runs until there a no more choices with unassigned rides or all choices are over the simulation time.
    Types::Choices newChoices;

    while(true) {
        // Generator
        for(std::unique_ptr<Types::Choice>& choice : choices) {
            // If valid choice exists, generate new choices and save in newChoices
            if(choice->unassigned.size() > 0 && checkCarDataValid(choice->cars, inputData.maxTime)) {
                std::unique_ptr<Types::CarData> newCars(new Types::CarData(choice->cars));
                generator.generate(newChoices, choice->searchGraphNode, choice->unassigned,
                                   std::move(newCars));
            }
        }

        // Aggregator
        // If new choices exists, aggregate those. Otherwise stop this while loop.
        if(newChoices.size() > 0) {
            aggregator.aggregate(newChoices);
            choices = std::move(newChoices);
            newChoices.clear();
            std::cout << std::round((inputData.nRides - choices.front()->unassigned.size()) * 100.0 /
                                    inputData.nRides) << "% of rides are assigned." << std::endl;
        } else {
            std::cout << "No more choices to aggregate." << std::endl;
            std::cout << "Printing best choice:" << std::endl;
            DBG_PRINT_CHOICE(choices.front());

            unsigned googleScore = 0;

            for(int i = 0; i < inputData.fleetSize; ++i) {
                googleScore += choices.front()->cars.p(i);
            }

            std::cout << "Final score: " << googleScore << std::endl;

            std::cout << "Writing output file.." << std::endl;
            choices.front()->searchGraphNode->writeToFile(outputPath, inputData.fleetSize);
            break;
        }
    }

}
