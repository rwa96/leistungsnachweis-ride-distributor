#ifndef RLAP_SOLVER_JV_H
#define RLAP_SOLVER_JV_H

#include <list>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Tensor.hpp"
#include "RLAPSolver.hpp"

/*************** CONSTANTS  *******************/
#define BIG 100000


class RLAPSolverJV : public RLAPSolver {
public:
	RLAPSolverJV(const Tensor<int>& mat);
    void solve(Tensor<unsigned>& assignments) override;
private:
	const unsigned rows, cols, size;
	std::vector<std::vector<double>> costMat;

	double lap(int dim,
		const std::vector<std::vector<double>>&assigncost,
		std::vector<int>&rowsol,
		std::vector<int>&colsol,
		std::vector<double>&u,
		std::vector<double>&v);
};

#endif // RLAP_SOLVER_JV_H
