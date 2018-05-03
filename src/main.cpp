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
	if (argc == 3)
	{

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

		unsigned nTries = 4;
		unsigned kBest = 2;
		unsigned beamSize = 3;

		// Generator + first Generator run
		Generator generator(*inputData, nTries, kBest);
		Types::Choices choices;
		std::vector<int> unassigned(inputData->nRides);
		std::iota(unassigned.begin(), unassigned.end(), 0);
		std::unique_ptr<Types::CarData> cars(new Types::CarData(inputData->fleetSize));
		std::shared_ptr<SearchGraphNode> parentNode;
		generator.generate(choices, parentNode, unassigned, std::move(cars));

		std::cout << "--- Generator ---" << std::endl;
		for (std::unique_ptr<Types::Choice> &choice : choices)
		{
			printChoice(choice);
		}
		std::cout << '\n'
				  << std::endl;

		// Aggregator + first Aggregator run
		Aggregator aggregator(*inputData, beamSize);
		aggregator.aggregate(choices);

		std::cout << "--- Aggregator ---" << std::endl;
		std::cout << "Picked beamsize best choices." << std::endl;
		for (std::unique_ptr<Types::Choice> &choice : choices)
		{
			std::cout << "Score: " << choice->score << std::endl;
		}
		std::cout << '\n'
				  << std::endl;

		// Main while loop, which finds best choice.
		// Runs until there a no more choices with unassigned rides or all choices are over the simulation time.
		Types::Choices newChoices;

		while (true)
		{

			for (std::unique_ptr<Types::Choice> &choice : choices)
			{

				if (choice->unassigned.size() > 0 && checkCarTime(choice->cars, inputData->maxTime))
				{
					std::unique_ptr<Types::CarData> newCars(new Types::CarData(choice->cars));
					generator.generate(newChoices, choice->searchGraphNode, choice->unassigned, std::move(newCars));
				}
			}

			std::cout << "--- Generator ---" << std::endl;
			for (std::unique_ptr<Types::Choice> &choice : choices)
			{
				printChoice(choice);
			}
			std::cout << '\n'
					  << std::endl;

			if (newChoices.size() > 0)
			{

				aggregator.aggregate(newChoices);
				std::cout << "--- Aggregator ---" << std::endl;
				std::cout << "Picked beamsize best choices." << std::endl;
				for (std::unique_ptr<Types::Choice> &choice : choices)
				{
					std::cout << "Score: " << choice->score << std::endl;
				}
				std::cout << '\n'
						  << std::endl;

				choices = std::move(newChoices);
				newChoices.clear();
			}
			else
			{

				std::cout << "No more choices to aggregate." << std::endl;
				std::cout << "Printing best choice:" << std::endl;
				printChoice(choices.front());
				choices.front()->searchGraphNode->writeToFile(argv[2], inputData->fleetSize);
				break;
			}
		}
	}
	else
	{
		std::cerr << "No input and output path argument set." << std::endl;
		return 1;
	}
	return 0;
}