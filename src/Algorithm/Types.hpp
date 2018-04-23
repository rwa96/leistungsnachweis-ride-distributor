#ifndef TYPES_H
#define TYPES_H

#include <memory>
#include <vector>
#include <initializer_list>
#include "Tensor.hpp"

namespace Types {

/**
 * Position, point in time and gained points of each car
 */
struct CarData {
    /**
     * Creates a zero initialized CarData object for a given amount of cars.
     *
     * \param [in] size Number of cars
     */
    CarData(const unsigned size) :
        x({size}), y({size}), t({size}), p({size}) 
	{
		for (unsigned i = 0; i < size; ++i) {
			x(i) = 0; y(i) = 0; t(i) = 0; p(i) = 0;
		}
	};

    /**
     * Creates a copy of an existing CarData object.
     *
     * \param [in] other Object to copy
     */
    CarData(CarData& other):
        x(other.x), y(other.y), t(other.t), p(other.p) {};

    /** X position of each car. */
    Tensor<int> x;
    /** Y Position of each car. */
    Tensor<int> y;
    /** Point in time for each car. */
    Tensor<int> t;
    /** Gained points of each car. */
    Tensor<int> p;
};

/**
 * Represenation of one node in the search tree, containing information about each car
 * and not yet assigned rides as well as a score for this choice.
 */
struct Choice {
    /**
     * Creates a new Choice instance by copying a given CarData object
     * and initializing everything else with default values.
     *
     * \param [in] other CarData object to copy
     */
    Choice(CarData& other):
        cars(other), score(0) {};

    /** Resulting CarData for this choice. */
    CarData cars;
    /** Unassigned rides for subsequent choices. */
    std::vector<int> unassigned;
    /** Score of this choice. */
    float score;
	/** Parent of this choice. */
	Choice* parent;
};

/** Independed Choices on could take (same level on the search graph). */
using Choices = std::vector<std::unique_ptr<Choice>>;

}

#endif // TYPES_H
