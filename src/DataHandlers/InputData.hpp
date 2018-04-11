#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <fstream>
#include <string>
#include "Tensor.hpp"

/**
 * Represenation of the input file defined by Google-HashCode's problem statement
 * 
 * \attention When parsing a file no format checks are made which could lead to undefined
 * \attenrion behaviour if the file format is invalid.
 */
struct InputData{

	/**
	 * Parses a file specified with path.
	 *
	 * \param [in] path file to fetch data from
	 * \throw std::fstream::failure if unable to open specified file 
	 */
    InputData(const std::string path);

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
	Tensor startX;
	/** column coordinate of all starting intersections. */
	Tensor startY;
	/** row coordinate of all finish intersections. */
	Tensor endX;
	/** column of all finish intersections. */
	Tensor endY;
	/** earliest starts. */
	Tensor startT;
	/** latest finishes. */
	Tensor endT; 
	/** distances of each ride. */
	Tensor distances;

};

#endif // INPUTDATA_H
