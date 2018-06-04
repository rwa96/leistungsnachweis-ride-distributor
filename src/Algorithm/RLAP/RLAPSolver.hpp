#ifndef RLAP_SOLVER_H
#define RLAP_SOLVER_H

#include "Tensor.hpp"

/**
 * This is an abstract representation of a rectangular linear assignment problem solver.
 *
 * \note Additional input needed by specific implementations should be in the constructor.
 */
class RLAPSolver {
public:
    /**
     * Writes the solution of a given linear assignment problem to a given Tensor (n rows, 2 columns)
     *
     * \note Since the required inputs for RLAP solvers differ, they are not specified here
     *
     * \param assignments Tensor for the RLAP solution (must have the correct size)
     */
    virtual void solve(Tensor<unsigned>& assignments) = 0;
};

#endif // RLAP_SOLVER_H
