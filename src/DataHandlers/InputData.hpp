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
 * \attention behaviour if the file format is invalid.
 */
struct InputData {

    /**
     * Given a valid path to an input file, this method creates a InputData representation of it.
     * \note no format checks on the file are performed.
     *
     * \param [in] path Path to input file
     * \throw std::fstream::failure if invalid file/path
     * \return std::shared_ptr<InputData> generated object
     */
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
    /** Number of vehicles in the fleet. */
    unsigned fleetSize;
    /** Number of rides. */
    unsigned nRides;
    /** Per-ride bonus for starting the ride on time. */
    unsigned bonus;
    /** Number of steps in the simulation. */
    unsigned maxTime;
    /** Row coordinate of all starting intersections. */
    Tensor<int> startX;
    /** Column coordinate of all starting intersections. */
    Tensor<int> startY;
    /** Row coordinate of all finish intersections. */
    Tensor<int> endX;
    /** Column of all finish intersections. */
    Tensor<int> endY;
    /** Earliest starts. */
    Tensor<int> startT;
    /** Latest finishes. */
    Tensor<int> endT;
    /** Distances of each ride. */
    Tensor<int> distances;

private:

    /**
     * Used by InputData::genFromFile to create an instance.
     *
     * \param [in] rows Rows of the road network
     * \param [in] cols Columns of road network
     * \param [in] fleetSize number of cars available
     * \param [in] nRides number of rides to be assigned
     * \param [in] bonus Bonus for in time arivals
     * \param [in] maxTime Steps of the simulation
     * \param [in,out] file input file
     * \throw std::fstream::failure if invalid file/path
     */
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
