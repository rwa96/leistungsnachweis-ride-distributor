#include <functional>
#include <algorithm>
#include "RLAPSolver.hpp"

void RLAPSolver::minimizeRowsAndCols(const Tensor<int>& minRowValues){
    Tensor<int> minColValues(minRowValues.getDims());
    std::unordered_set<unsigned> nonZeroCols(indexElements.begin(), indexElements.end());

    for(unsigned row = 0; row < rows; ++row){
        for(unsigned col = 0; col < cols; ++col){
            int& entry = matrix(row, col);
            entry -= minRowValues(row);
            if(entry == 0){
                zeros.push_back({row, col});
                deleted.push_back(false);
                nonZeroCols.erase(col);
            }else if(entry < minColValues(col)){
                minColValues(col) = entry;
            }
        }
		if (rectangular && moreRows) {
			fillMatrix(row) -= minRowValues(row);
		}
    }

    for(unsigned col: nonZeroCols){
        for(unsigned row = 0; row < size; ++row){
            int& entry = matrix(row, col);
            entry -= minColValues(col);
            if(entry == 0){
                zeros.push_back({row, col});
                deleted.push_back(false);
            }
        }
    }
}

void RLAPSolver::coverZeros(){
    auto iCoordItr = zeros.begin();
    auto iDeletedItr = deleted.begin();
    while(iCoordItr != zeros.end()){
        const std::pair<unsigned, unsigned>& iCoord = *iCoordItr;
        bool& iDeleted = *iDeletedItr;

        if(iDeleted){continue;}

        bool uniqueRow = true, uniqueCol = true;
        std::list<std::reference_wrapper<bool>> del;

        auto jCoordItr = zeros.begin();
        auto jDeletedItr = deleted.begin();
        while(jCoordItr != zeros.end()){
            const std::pair<unsigned, unsigned>& jCoord = *jCoordItr;
            bool& jDeleted = *jDeletedItr;

            if(jDeleted){continue;}
            if(iCoord == jCoord){
                del.push_back(jDeleted);
                continue;
            }

            if(iCoord.first == jCoord.first){
                uniqueRow = false;
                del.push_back(jDeleted);
            }
            if(iCoord.second == jCoord.second){
                uniqueCol = false;
                del.push_back(jDeleted);
            }

            ++jCoordItr;
            ++jDeletedItr;
        }
        if(uniqueRow || uniqueCol){
            if(uniqueRow){unmarkedCols.erase(iCoord.second);}
            else{unmarkedRows.erase(iCoord.first);}
            for(bool& elm: del){
                elm = true;
            }
        }

        ++iCoordItr;
        ++iDeletedItr;
    }

}

void RLAPSolver::minimizeRemaining(int& globalMin){
    int newGlobalMin = 0;
    for(unsigned row: unmarkedRows){
        for(unsigned col: unmarkedCols){
            int& entry = matrix(row, col);
            entry -= globalMin;
            if(entry == 0){
                zeros.push_back({row, col});
                deleted.push_back(false);
            }else if(newGlobalMin == 0 || entry < newGlobalMin){
                newGlobalMin = entry;
            }
        }
    }

    globalMin = newGlobalMin;
}

void RLAPSolver::assignResult(Tensor<int>& assignments) {
	std::unordered_set<unsigned> selectedRows;
	unsigned nAssignments = std::min(rows, cols);
	unsigned outIndex = 0;
	while (selectedRows.size() < nAssignments) {
		for (std::pair<unsigned, unsigned> zero : zeros) {
			if (zero.first < rows && 
				zero.second < cols &&
				selectedRows.find(zero.first) == selectedRows.end()) 
			{
				assignments(outIndex, 0) = zero.first;
				assignments(outIndex, 1) = zero.second;
				selectedRows.insert(zero.first);
				++outIndex;
			}
		}
	}
}

void RLAPSolver::solve(const Tensor<int>& minRowValues, Tensor<int>& assignments){
    minimizeRowsAndCols(minRowValues);
    coverZeros();

    int globalMin = 0;
    for(unsigned row: unmarkedRows){
        for(unsigned col: unmarkedCols){
            if(globalMin == 0 || matrix(row, col) < globalMin){
                globalMin = matrix(row, col);
            }
        }
    }
    while(unmarkedRows.size() + unmarkedCols.size() > size){
        minimizeRemaining(globalMin);
        coverZeros();
    }

    assignResult(assignments);
}
