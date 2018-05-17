#ifndef RLAP_SOLVER_H
#define RLAP_SOLVER_H

#include <list>
#include <unordered_set>
#include "Tensor.hpp"

class RLAPSolver {
public:
    RLAPSolver(Tensor<int>& matrix, const int maxEntry):
        size(std::max(matrix.getDims()[0], matrix.getDims()[1])),
        matrix(matrix){};
	virtual void solve(const Tensor<int>& minRowValues, Tensor<int>& assignments) = 0;

protected:
    const unsigned size;
    const Tensor<int> matrix;
};

#endif // RLAP_SOLVER_H
