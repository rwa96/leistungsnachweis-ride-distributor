#ifndef RLAP_SOLVER_HUNGARIAN_H
#define RLAP_SOLVER_HUNGARIAN_H

#include <numeric>
#include <list>
#include <vector>
#include <unordered_set>
#include "RLAPSolver.hpp"


class RLAPSolverHungarian : public RLAPSolver {
public:
    RLAPSolverHungarian(const Tensor<int>& matrix, const Tensor<int>& minRowValues, const int maxEntry);
	void solve(Tensor<int>& assignments) override;

private:
    const unsigned size, rows, cols;
    const Tensor<int> matrix;
    std::vector<unsigned> indexElements;
    std::list<std::pair<unsigned, unsigned>> zeros;
    std::list<bool> deleted;
    std::unordered_set<unsigned> unmarkedCols, unmarkedRows;
    Tensor<int> minRowValues;

    void fillMatrix();
    void minimizeRowsAndCols();
    void coverZeros();
    void minimizeRemaining(int& globalMin);
    void assignResult(Tensor<int>& assignments);
};

#endif // RLAP_SOLVER_HUNGARIAN_H
