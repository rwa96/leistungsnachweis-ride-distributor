#ifndef ALGORITHM_H
#define ALGORHITM_H

#include "Generator.hpp"
#include "Aggregator.hpp"

class Algorithm {
public:

	/**
	* Generate a new Algorithm.
	*/
	Algorithm(InputData& inputData, std::string outputPath, unsigned nTries, unsigned kBest, unsigned beamSize) :
		inputData(inputData), outputPath(outputPath), nTries(nTries), kBest(kBest), beamSize(beamSize), generator(inputData, nTries, kBest),
		aggregator(inputData, beamSize) {};

	void run();

private:

	void printChoice(std::unique_ptr<Types::Choice> &choice);
	bool checkCarTime(Types::CarData carData, unsigned T);

	/** InputData representing the simulation enviroment. */
	InputData& inputData;
	std::string outputPath;
	unsigned nTries;
	unsigned kBest;
	/** Amount of choices to keep. */
	unsigned beamSize;
	Generator generator;
	Aggregator aggregator;

};

#endif // ALGORITHM_H
