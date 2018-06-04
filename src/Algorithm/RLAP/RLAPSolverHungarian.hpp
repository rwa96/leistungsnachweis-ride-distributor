#ifndef RLAP_SOLVER_HUNGARIAN_H
#define RLAP_SOLVER_HUNGARIAN_H

#include <vector>
#include "Tensor.hpp"
#include "RLAPSolver.hpp"

/**
 * Implementation for solving the rectangular linear assignment problem
 * ([more info here](http://www.optimization-online.org/DB_FILE/2008/10/2115.pdf)).
 * The solver variant used here is called [Hungarian Algorithm](https://www.wikihow.com/Use-the-Hungarian-Algorithm).
 */
class RLAPSolverHungarian : public RLAPSolver {
public:
    RLAPSolverHungarian(const Tensor<int>& mat, const int maxCost);
    void solve(Tensor<unsigned>& assignments) override;
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
    unsigned coverZeros(Tensor<unsigned>& zeroCountRows, Tensor<unsigned>& zeroCountCols,
                        Tensor<bool>& rowLines, Tensor<bool>& colLines);
    int recalculateCosts(const int minVal, Tensor<unsigned>& zeroCountRows,
                         Tensor<unsigned>& zeroCountCols, Tensor<bool>& rowLines, Tensor<bool>& colLines);
    void assignMatching(Tensor<unsigned>& assignments, Tensor<unsigned>& zeroCountRows,
                        Tensor<unsigned>& zeroCountCols);
};

#endif // RLAP_SOLVER_HUNGARIAN_H
