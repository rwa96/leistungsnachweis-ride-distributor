#ifndef RLAP_SOLVER_HUNGARIAN_H
#define RLAP_SOLVER_HUNGARIAN_H

#include "Tensor.hpp"
#include "RLAPSolver.hpp"

typedef enum {
    HUNGARIAN_NOT_ASSIGNED,
    HUNGARIAN_ASSIGNED,
} ASSIGN;

class RLAPSolverHungarian : public RLAPSolver {
public:
    RLAPSolverHungarian(const Tensor<int>& mat, const unsigned rows, const unsigned cols,
                        const int maxCost);
    void solve(Tensor<int>& assignments) override;
private:
    unsigned cost, rows, cols, size;
    Tensor<int> costMat, assignMat;

};

#endif // RLAP_SOLVER_HUNGARIAN_H
