#include <functional>
#include <algorithm>
#include <iostream>
#include "RLAPSolverHungarian.hpp"

#define MAX_SIZE(m) std::max(m.getDims()[0], m.getDims()[1])

void RLAPSolverHungarian::fillMatrix(){
    unsigned row, col;
    if(rows < cols){
        row = 0; col = cols;
    }else{
        row = rows; col = 0;
    }

    for(; row < size; ++row){
        for(; col < size; ++col){
            matrix(row, col) = 0;
        }
    }
}

RLAPSolverHungarian::RLAPSolverHungarian(const Tensor<int>& matrix, const Tensor<int>& minRowValues, const int maxEntry):
    rows(matrix.getDims()[0]),
    cols(matrix.getDims()[1]),
    size(MAX_SIZE(matrix)),
    indexElements({MAX_SIZE(matrix)}),
    matrix({MAX_SIZE(matrix), MAX_SIZE(matrix)})
{
    this->minRowValues = minRowValues;
    std::iota(indexElements.begin(), indexElements.end(), 0);
    unmarkedCols.insert(indexElements.begin(), indexElements.end());
    unmarkedRows.insert(indexElements.begin(), indexElements.end());
    for(unsigned row = 0; row < rows; ++row){
        for(unsigned col = 0; col < cols; ++col){
            this->matrix(row, col) = maxEntry - matrix(row, col);
        }
        minRowValues(row) = maxEntry - minRowValues(row);
    }
    if(rows != cols){
        fillMatrix();
    }
}

void RLAPSolverHungarian::minimizeRowsAndCols(){
    Tensor<int> minColValues({cols}, 0);
    std::unordered_set<unsigned> nonZeroCols(indexElements.begin(), indexElements.end());

    for(unsigned row = 0; row < size; ++row){
        for(unsigned col = 0; col < size; ++col){
            int& entry = matrix(row, col);
            entry -= minRowValues(row);
            if(entry == 0){
                zeros.push_back({row, col});
                deleted.push_back(false);
                nonZeroCols.erase(col);
            }else if(minColValues(col) == 0 || entry < minColValues(col)){
                minColValues(col) = entry;
            }
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

void RLAPSolverHungarian::coverZeros(){
    for(unsigned i = 0; i < zeros.size(); ++i){
        if(deleted[i]){continue;}

        bool uniqueRow = true, uniqueCol = true;
        std::list<unsigned> deletedIndex;

        for(unsigned j = 0; j < zeros.size(); ++j){
            if(!uniqueRow && !uniqueCol){break;}
            if(deleted[j]){continue;}
            if(zeros[i] == zeros[j]){
                deletedIndex.push_back(j);
                continue;
            }

            if(zeros[i].first == zeros[j].first){
                uniqueRow = false;
                deletedIndex.push_back(j);
            }
            if(zeros[i].second == zeros[j].second){
                uniqueCol = false;
                deletedIndex.push_back(j);
            }
        }

        if(uniqueRow || uniqueCol){
            if(uniqueRow){unmarkedCols.erase(zeros[i].second);}
            else{unmarkedRows.erase(zeros[i].first);}
            for(unsigned index: deletedIndex){
                deleted[index] = true;
            }
        }
    }

}

void RLAPSolverHungarian::minimizeRemaining(int& globalMin){
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

void RLAPSolverHungarian::assignResult(Tensor<int>& assignments) {
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

void RLAPSolverHungarian::solve(Tensor<int>& assignments){
    minimizeRowsAndCols();
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
