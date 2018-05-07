#ifndef ALGORITHM_H
#define ALGORHITM_H

#include "Generator.hpp"
#include "Aggregator.hpp"

/**
 * Algorithm solving the problem statement of the HashCode online quallification round 2018 
 * by build a search graph containing available choices. 
 * Only the best choices are taken into consideration until there all rides has been assigned or no new ones can be assigned anymore.
 */
class Algorithm {
public:

	/**
	 * Prepare the algorithm by intalizing its parameter.
	 * 
	 * \param [in]	inputData	InputData representing the simulation enviroment.
	 * \param [out]	outputPath	Path of output file containing the calculated solution.
	 * \param [in]	nTries		Amount of choice groups generator randomly creates.
	 * \param [in]	kBest		Amount of best choices generator picks from the generated choices groups.
	 * \param [in]	beamSize	Amount of best choices aggregator keeps.
	 */
	Algorithm(InputData& inputData, std::string outputPath, unsigned nTries, unsigned kBest, unsigned beamSize) :
		inputData(inputData), outputPath(outputPath), nTries(nTries), kBest(kBest), beamSize(beamSize), generator(inputData, nTries, kBest),
		aggregator(inputData, beamSize) {};

	/**
	 * Run the algorithm, until all rides have been assigned or no new ones can be assigned anymore.
	 * Best choice is writen to the outputPath.
	 */
	void run();

private:

	/**
	 * Print a choice.
	 *
	 * \param [in]	choice	Choice to print.
	 */
	void printChoice(std::unique_ptr<Types::Choice> &choice);

	/**
	 * Check if carData is still within a given simulation time.
	 *
	 * \param [in]	carData	CarData to check.
	 * \param [in]	T		Max. valid simulation time.
	 * \return true if carData is valid, otherwise false.
	 */
	bool checkCarDataValid(Types::CarData carData, unsigned T);

	/** InputData representing the simulation enviroment. */
	InputData& inputData;
	/** Path of output file. */
	std::string outputPath;
	/** Amount of choice groups generator randomly creates. */
	unsigned nTries;
	/** Amount of best choices generator picks from the generated choices groups. */
	unsigned kBest;
	/** Amount of best choices aggregator keeps. */
	unsigned beamSize;
	/** Generator trying to find the best choices. */
	Generator generator;
	/** Aggregator picking the best choices from a set of given ones. */
	Aggregator aggregator;

};

#endif // ALGORITHM_H
