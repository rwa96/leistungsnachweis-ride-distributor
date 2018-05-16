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
    void solve(const Tensor<int>& minRowValues, Tensor<int>& assignments);
private:
    const unsigned size;
    const Tensor<int> matrix;
    std::list<std::pair<unsigned, unsigned>> zeros;
    std::list<bool> deleted;
    std::unordered_set<unsigned> unmarkedRows, unmarkedCols;

    void minimizeRowsAndCols(const Tensor<int>& minRowValues);
    void coverZeros();
    void minimizeRemaining(int& globalMin);
    void assignResult(Tensor<int>& assignments);
};

#endif // RLAP_SOLVER_H
