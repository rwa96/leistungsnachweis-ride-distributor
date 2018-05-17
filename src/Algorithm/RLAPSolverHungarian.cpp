#include <algorithm>
#include <functional>
#include "RLAPSolver.hpp"

class RLAPSolverHungarian : public RLAPSolver {

	std::list<std::pair<unsigned, unsigned>> zeros;
	std::list<bool> deleted;
	std::unordered_set<unsigned> unmarkedRows, unmarkedCols;

	void minimizeRowsAndCols(const Tensor<int>& minRowValues) {
		Tensor<int> minColValues(minRowValues.getDims());
		std::unordered_set<unsigned> nonZeroCols;

		for (unsigned row = 0; row < RLAPSolver::size; ++row) {
			for (unsigned col = 0; col < RLAPSolver::size; ++col) {
				int& entry = RLAPSolver::matrix(row, col);
				entry -= minRowValues(row);
				if (entry == 0) {
					zeros.push_back({ row, col });
					deleted.push_back(false);
					nonZeroCols.erase(col);
				}
				else if (entry < minColValues(col)) {
					minColValues(col) = entry;
				}
			}
		}

		for (unsigned col : nonZeroCols) {
			for (unsigned row = 0; row < RLAPSolver::size; ++row) {
				int& entry = RLAPSolver::matrix(row, col);
				entry -= minColValues(col);
				if (entry == 0) {
					zeros.push_back({ row, col });
					deleted.push_back(false);
				}
			}
		}
	}

	void coverZeros() {
		auto iCoordItr = zeros.begin();
		auto iDeletedItr = deleted.begin();
		while (iCoordItr != zeros.end()) {
			const std::pair<unsigned, unsigned>& iCoord = *iCoordItr;
			bool& iDeleted = *iDeletedItr;

			if (iDeleted) { continue; }

			bool uniqueRow = true, uniqueCol = true;
			std::list<std::reference_wrapper<bool>> del;

			auto jCoordItr = zeros.begin();
			auto jDeletedItr = deleted.begin();
			while (jCoordItr != zeros.end()) {
				const std::pair<unsigned, unsigned>& jCoord = *jCoordItr;
				bool& jDeleted = *jDeletedItr;

				if (jDeleted) { continue; }
				if (iCoord == jCoord) {
					del.push_back(jDeleted);
					continue;
				}

				if (iCoord.first == jCoord.first) {
					uniqueRow = false;
					del.push_back(jDeleted);
				}
				if (iCoord.second == jCoord.second) {
					uniqueCol = false;
					del.push_back(jDeleted);
				}

				++jCoordItr;
				++jDeletedItr;
			}
			if (uniqueRow || uniqueCol) {
				if (uniqueRow) { unmarkedCols.erase(iCoord.second); }
				else { unmarkedRows.erase(iCoord.first); }
				for (bool& elm : del) {
					elm = true;
				}
			}

			++iCoordItr;
			++iDeletedItr;
		}

	}

	void minimizeRemaining(int& globalMin) {
		int newGlobalMin = 0;
		for (unsigned row : unmarkedRows) {
			for (unsigned col : unmarkedCols) {
				int& entry = RLAPSolver::matrix(row, col);
				entry -= globalMin;
				if (entry == 0) {
					zeros.push_back({ row, col });
					deleted.push_back(false);
				}
				else if (newGlobalMin == 0 || entry < newGlobalMin) {
					newGlobalMin = entry;
				}
			}
		}

		globalMin = newGlobalMin;
	}


	void assignResult(Tensor<int>& assignments) {

	}

	virtual void solve(const Tensor<int>& minRowValues, Tensor<int>& assignments) override {
		minimizeRowsAndCols(minRowValues);
		coverZeros();

		int globalMin = 0;
		for (unsigned row : unmarkedRows) {
			for (unsigned col : unmarkedCols) {
				if (globalMin == 0 || RLAPSolver::matrix(row, col) < globalMin) {
					globalMin = RLAPSolver::matrix(row, col);
				}
			}
		}
		while (unmarkedRows.size() + unmarkedCols.size() > RLAPSolver::size) {
			minimizeRemaining(globalMin);
			coverZeros();
		}

		assignResult(assignments);
	}

};
