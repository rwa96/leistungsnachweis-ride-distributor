#ifndef RLAP_SOLVER_HUNGARIAN_H
#define RLAP_SOLVER_HUNGARIAN_H

#include <vector>
#include "Tensor.hpp"
#include "RLAPSolver.hpp"


class RLAPSolverHungarian : public RLAPSolver {
public:
    RLAPSolverHungarian(const Tensor<int>& mat, const int maxCost);
    void solve(Tensor<int>& assignments) override;
private:
    struct Zero {
        unsigned row;
        unsigned col;
        bool deleted;
    };

    const unsigned rows, cols, size;
    Tensor<int> costMat, rowMin, colMin;
    std::vector<Zero> zeros;
    bool solved;

    void reduceRowsAndCols(Tensor<unsigned>& zeroCountRows, Tensor<unsigned>& zeroCountCols);
    unsigned coverZeros(Tensor<unsigned>& zeroCountRows, Tensor<unsigned>& zeroCountCols, Tensor<bool>& rowLines, Tensor<bool>& colLines);
    int recalculateCosts(const int minVal, Tensor<unsigned>& zeroCountRows, Tensor<unsigned>& zeroCountCols, Tensor<bool>& rowLines, Tensor<bool>& colLines);
    void assignMatching(Tensor<int>& assignments);
};

#endif // RLAP_SOLVER_HUNGARIAN_H
