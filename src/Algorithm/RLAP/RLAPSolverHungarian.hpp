#ifndef RLAP_SOLVER_HUNGARIAN_H
#define RLAP_SOLVER_HUNGARIAN_H

#include <memory>
#include <numeric>
#include <list>
#include <vector>
#include <unordered_set>
#include "RLAPSolver.hpp"


class RLAPSolverHungarian : public RLAPSolver {
public:
    RLAPSolverHungarian(Tensor<int>& matrix, std::unique_ptr<Tensor<int>> minRowValues, const int maxEntry) :
        rows(matrix.getDims()[0]),
        cols(matrix.getDims()[1]),
        size(std::max(rows, cols)),
        rectangular(rows != cols),
        moreRows(rows < cols),
        indexElements(size),
        minRowValues(std::move(minRowValues)),
        matrix(matrix),
        fillMatrix({rectangular ? (moreRows ? rows : cols) : 0}, maxEntry)
    {
        std::iota(indexElements.begin(), indexElements.end(), 0);
        unmarkedCols.insert(indexElements.begin(), indexElements.end());
        unmarkedRows.insert(indexElements.begin(), indexElements.end());
    }

	void solve(Tensor<int>& assignments) override;

private:
    const bool rectangular, moreRows;
    const unsigned size, rows, cols;
    const Tensor<int> matrix, fillMatrix;
    std::vector<unsigned> indexElements;
    std::list<std::pair<unsigned, unsigned>> zeros;
    std::list<bool> deleted;
    std::unordered_set<unsigned> unmarkedCols, unmarkedRows;
    std::unique_ptr<Tensor<int>> minRowValues;

    void minimizeRowsAndCols();
    void coverZeros();
    void minimizeRemaining(int& globalMin);
    void assignResult(Tensor<int>& assignments);
};

#endif // RLAP_SOLVER_HUNGARIAN_H
