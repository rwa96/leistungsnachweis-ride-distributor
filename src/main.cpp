#include <iostream>
#include <fstream>
#include <memory>
#include <numeric>
#include "InputData.hpp"
#include "Generator.hpp"
#include "Aggregator.hpp"
#include "SearchGraphNode.hpp"

void printChoice(std::unique_ptr<Types::Choice> &choice)
{
	std::cout << "Choice:" << std::endl;
	std::cout << '\t' << "x: " << choice->cars.x.str();
	std::cout << '\t' << "y: " << choice->cars.y.str();
	std::cout << '\t' << "t: " << choice->cars.t.str();
	std::cout << '\t' << "p: " << choice->cars.p.str();
	std::cout << '\t' << "Score: " << choice->score << std::endl;
}

bool checkCarTime(Types::CarData carData, unsigned T)
{
	bool result = false;

	for (int i = 0; i < carData.t.getSize(); i++)
	{
		if (carData.t(i) < T)
		{
			result = true;
			break;
		}
	}

	return result;
}

int main(int argc, char *argv[])
{
	if (argc != 6)
	{
		std::cerr << "No input path, output path, nTries, kBest and beamSize argument set." << std::endl;
		return 1;
	}

	unsigned nTries = atoi(argv[3]);
	unsigned kBest = atoi(argv[4]);
	unsigned beamSize = atoi(argv[5]);

	// InputData
	std::shared_ptr<InputData> inputData;
	try
	{
		inputData = InputData::genFromFile(argv[1]);
	}
	catch (const std::fstream::failure e)
	{
		std::cerr << e.what() << "(Invalid file or path)" << std::endl;
		return 1;
	}

	// Setup Generator and requirements, then do first Generator run
	Generator generator(*inputData, nTries, kBest);

	Types::Choices choices;
	std::vector<int> unassigned(inputData->nRides);
	std::iota(unassigned.begin(), unassigned.end(), 0);
	std::unique_ptr<Types::CarData> cars(new Types::CarData(inputData->fleetSize));
	std::shared_ptr<SearchGraphNode> parentNode;

	generator.generate(choices, parentNode, unassigned, std::move(cars));

	// Setup Aggregator, then do first Aggregator run
	Aggregator aggregator(*inputData, beamSize);
	aggregator.aggregate(choices);

	// Main while loop, which finds best choice.
	// Runs until there a no more choices with unassigned rides or all choices are over the simulation time.
	Types::Choices newChoices;

	while (true)
	{
		// Generator
		for (std::unique_ptr<Types::Choice> &choice : choices)
		{
			// If valid choice exists, generate new choices and save in newChoices
			if (choice->unassigned.size() > 0 && checkCarTime(choice->cars, inputData->maxTime))
			{
				std::unique_ptr<Types::CarData> newCars(new Types::CarData(choice->cars));
				generator.generate(newChoices, choice->searchGraphNode, choice->unassigned, std::move(newCars));
			}
		}

		// Aggregator
		// If new choices exists, aggregate those. Otherwise stop this while loop.
		if (newChoices.size() > 0)
		{
			aggregator.aggregate(newChoices);
			choices = std::move(newChoices);
			newChoices.clear();
			std::cout << (inputData->nRides - choices.front()->unassigned.size()) * 100.0 / inputData->nRides << "%" << std::endl;
		}
		else
		{
			std::cout << "No more choices to aggregate." << std::endl;
			std::cout << "Printing best choice:" << std::endl;
			printChoice(choices.front());

			unsigned score = 0;
			for (int i = 0; i < inputData->fleetSize; ++i) {
				score += choices.front()->cars.p(i);
			}
			std::cout << "Google score: " << score << std::endl;

			std::cout << "Writing output file.." << std::endl;
			choices.front()->searchGraphNode->writeToFile(argv[2], inputData->fleetSize);
			break;
		}
	}

	return 0;
}