#ifndef RLAP_SOLVER_H
#define RLAP_SOLVER_H

#include <list>
#include <unordered_set>
#include <numeric>
#include "Tensor.hpp"

class RLAPSolver {
public:
	RLAPSolver(Tensor<int>& matrix, const int maxEntry) :
		rows(matrix.getDims()[0]),
		cols(matrix.getDims()[1]),
		size(std::max(rows, cols)),
		rectangular(rows != cols),
		moreRows(rows < cols),
		indexElements(size),
        matrix(matrix),
		fillMatrix({rectangular ? (moreRows ? rows : cols) : 0}, maxEntry)
	{
		std::iota(indexElements.begin(), indexElements.end(), 0);
		unmarkedRows.insert(indexElements.begin(), indexElements.end());
		unmarkedCols.insert(indexElements.begin(), indexElements.end());
	};
    void solve(const Tensor<int>& minRowValues, Tensor<int>& assignments);
private:
	const bool rectangular, moreRows;
    const unsigned size, rows, cols;
    const Tensor<int> matrix, fillMatrix;
	std::vector<unsigned> indexElements;
    std::list<std::pair<unsigned, unsigned>> zeros;
    std::list<bool> deleted;
    std::unordered_set<unsigned> unmarkedRows, unmarkedCols;

    void minimizeRowsAndCols(const Tensor<int>& minRowValues);
    void coverZeros();
    void minimizeRemaining(int& globalMin);
    void assignResult(Tensor<int>& assignments);
};

#endif // RLAP_SOLVER_H
