#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include "Types.hpp"
#include "InputData.hpp"

/**
 * Pick the best choices out of a set of given one.
 */
class Aggregator {
public:

    /**
     * Generate a new Aggregator.
     *
     * \param [in] inputData InputData representing the simulation enviroment
     * \param [in] beamSize Amount of choices to keep
     */
    Aggregator(InputData& inputData, unsigned beamSize) :
        inputData(inputData), beamSize(beamSize) {};

    /**
     * Go through a list of choices and pick the beamsize best ones.
     * \param [in] choices Choices to go through
     */
    void aggregate(Types::Choices& choices);

private:

    /**
     * Compare two choices descending by score.
     * \param [in] lhs First choice used for comparison
     * \param [in] rhs Second choice used for comparison
     * \return bool true if first choice's score is greater then second choice's score. Otherwise false.
     */
    static bool sortByScore(const std::unique_ptr<Types::Choice>& lhs,
                            const std::unique_ptr<Types::Choice>& rhs);

    /** InputData representing the simulation enviroment. */
    InputData& inputData;

    /** Amount of choices to keep. */
    unsigned beamSize;

};

#endif // AGGREGATOR_H
