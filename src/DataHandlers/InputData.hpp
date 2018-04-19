#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <fstream>
#include <string>
#include <memory>
#include "Tensor.hpp"

/**
 * Represenation of the input file defined by Google-HashCode's problem statement
 *
 * \attention When parsing a file no format checks are made which could lead to undefined
 * \attenrion behaviour if the file format is invalid.
 */
struct InputData{

    static std::shared_ptr<InputData> genFromFile(const std::string path);

	/**
	 * Returns a string represenation of the input data.
	 *
	 * \return std::string
	 */
    std::string str() const;

	/** Number of rows of the grid. */
	unsigned rows;
	/** Number of columns of the grid. */
	unsigned cols;
	/** number of vehicles in the fleet. */
	unsigned fleetSize;
	/** number of rides. */
	unsigned nRides;
	/** per-ride bonus for starting the ride on time. */
	unsigned bonus;
	/** number of steps in the simulation. */
	unsigned maxTime;
	/** row coordinate of all starting intersections. */
	Tensor<int> startX;
	/** column coordinate of all starting intersections. */
	Tensor<int> startY;
	/** row coordinate of all finish intersections. */
	Tensor<int> endX;
	/** column of all finish intersections. */
	Tensor<int> endY;
	/** earliest starts. */
	Tensor<int> startT;
	/** latest finishes. */
	Tensor<int> endT;
	/** distances of each ride. */
	Tensor<int> distances;

private:

    InputData(
    	const unsigned rows,
    	const unsigned cols,
    	const unsigned fleetSize,
    	const unsigned nRides,
    	const unsigned bonus,
    	const unsigned maxTime,
        std::fstream& file
    );

};

#endif // INPUTDATA_H
