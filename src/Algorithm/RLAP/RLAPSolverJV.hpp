#ifndef RLAP_SOLVER_JV_H
#define RLAP_SOLVER_JV_H

#include "RLAPSolver.hpp"

class RLAPSolverJV : public RLAPSolver {

    void solve(Tensor<unsigned>& assignments) override;

};

#endif // RLAP_SOLVER_JV_H
