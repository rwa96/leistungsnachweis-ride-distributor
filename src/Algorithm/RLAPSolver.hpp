#ifndef RLAP_SOLVER_H
#define RLAP_SOLVER_H

#include <vector>
#include <memory>
#include "Tensor.hpp"

class RLAPSolver {
public:
    RLAPSolver(Tensor<int>& matrix, const int maxEntry):matrix(matrix){};
    void solve(const Tensor<int>& minRowValues);
private:
    const Tensor<int> matrix;
    std::list<std::pair<unsigned, unsigned>> zeros;
    std::list<bool> deleted;
    std::set<unsigned> unmarkedRows, unmarkedCols;

    void minimizeRowsAndCols(const Tensor<int>& minRowValues);
    void coverZeros();
    void minimizeRemaining(int& globalMin);
};

#endif // RLAP_SOLVER_H
