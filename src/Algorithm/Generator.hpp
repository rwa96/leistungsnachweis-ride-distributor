#ifndef GENERATOR_H
#define GENERATOR_H

#include <memory>
#include "Types.hpp"
#include "Tensor.hpp"
#include "InputData.hpp"
#include "SearchGraphNode.hpp"

/**
 * Finds the best possible way to distribute one ride to each car given
 * a list of unassigned rides and a list of cars with their positions gained points and points in time.
 */
class Generator {
public:

	/**
	 * Creates a generator of choices on given input data.
	 *
	 * \param [in] inputData used internally to get specific information about rides
	 */
    Generator(InputData& inputData):inputData(inputData){};

	/**
	 * Given the current state of the search process this generates the next optimal choice to take.
	 * 
	 * \note This method should be called repeatedly using its result until the searchpath is complete
	 *
	 * \param [in] prevNode is referenced by the new SearchGraphNode of the returned Choice
	 * \param [in] unassigned a list of indices of all unassigned rides
	 * \param [in] cars represents the current state of all cars
	 * \return std::unique_ptr<Types::Choice> optimal way to assign one ride to each car
	 */
    std::unique_ptr<Types::Choice> generate(std::shared_ptr<SearchGraphNode>& prevNode,
                  std::vector<int>& unassigned,
                  std::unique_ptr<Types::CarData> cars);

private:

	/**
	 * Given a list of unassigned rides and current state of each car, this method
	 * calculates finish times and finish points for each car taking each unassigned ride
	 *
	 * \param [out] finishTimes CxR matrix (C:=numer of cars, R:=number of unassigned rides)
	 * \param [out] finishPoints CxR matrix (C:=numer of cars, R:=number of unassigned rides)
	 * \param [in] a list of indices of all unassigned rides
	 * \param [in] represents the current state of all cars
	 * \return int maximum value in finishPoints (used for hungarian algorithm)
	 */
    int createSearchSpace(Tensor<int>& finishTimes, Tensor<int>& finishPoints,
                          std::vector<int>& unassigned, std::unique_ptr<Types::CarData>& cars);

	/**
	 * Solves the rectangular linear assignment problem of choosing the maximal finishPoints and
	 * generates a choice out of it
	 * 
	 * \param [in] prevNode is referenced by the new SearchGraphNode of the returned Choice
	 * \param [in] finishPoints gained points for all cars taking all rides
	 * \param [in] unassigned a list of indices of all unassigned rides
	 * \param [in] maxValue in finishPoints (used for hungarian algorithm)
	 * \param [in] cars represents the current state of all cars
	 * \return std::unique_ptr<Types::Choice> optimal way to assign one ride to each car
	 */
	std::unique_ptr<Types::Choice> selectFromSearchSpace(std::shared_ptr<SearchGraphNode>& prevNode, Tensor<int>& finishTimes,
		Tensor<int>& finishPoints, std::vector<int>& unassigned,
		int maxValue, std::unique_ptr<Types::CarData>& cars);

	/** Used internally to get specific information about rides. */
    InputData& inputData;
};

#endif // GENERATOR_H
