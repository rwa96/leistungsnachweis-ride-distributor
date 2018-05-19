#ifndef RLAP_SOLVER_H
#define RLAP_SOLVER_H

#include "Tensor.hpp"

class RLAPSolver {
public:
	virtual void solve(Tensor<int>& assignments) = 0;
};

#endif // RLAP_SOLVER_H
