#include <stdexcept>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include "RLAPSolver.hpp"

void RLAPSolver::minimizeRowsAndCols(const Tensor<int>& minRowValues){
    Tensor<int> minColValues(minRowValues.getDims());
    std::set<unsigned> nonZeroCols();

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
    }

    for(unsigned col: nonZeroCols){
        for(unsigned row = 0; row < rows; ++row){
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
        std::list<std::pair<unsigned, unsigned>> del;

        auto jCoordItr = zeros.begin();
        auto jDeletedItr = deleted.begin();
        while(jCoordItr != zeros.end()){
            const std::pair<unsigned, unsigned>& jCoord = *jCoordItr;
            bool& jDeleted = *jDeletedItr;

            if(jDeleted){continue;}
            if(iCoord == jCoord){
                del.push_back(jCoord);
                continue;
            }
            
            if(iCoord.first == jCoord.first){
                uniqueRow = false;
                del.push_back(jCoord);
            }
            if(iCoord.second == jCoord.second){
                uniqueCol = false;
                del.push_back(jCoord);
            }

            ++jCoordItr;
            ++jDeletedItr;
        }
        if(uniqueRow || uniqueCol){
            if(uniqueRow){unmarkedCols.erase(iCoord.second);}
            else{unmarkedRows.erase(iCoord.first);}
            for(std::pair<unsigned, unsigned>& elm: del){
                iDeleted = true;
            }
        }

        ++iCoordItr;
        ++iDeletedItr;
    }

}

void RLAPSolver::minimizeRemaining(int& globalMin){
    for(unsigned row: unmarkedRows){
        for(unsigned col: unmarkedCols){
            if(globalMin == 0 || matrix(row, col) < globalMin){
                globalMin = matrix(row, col);
            }
        }
    }

    int newGlobalMin = 0;
    for(unsigned row: unmarkedRows){
        for(unsigned col: unmarkedCols){
            int& entry = matrix(row, col);
            entry -= globalMin;
            if(entry == 0){
                zeros.push_back({row, col});
            }else if(newGlobalMin == 0 || entry < newGlobalMin){
                newGlobalMin = entry;
            }
        }
    }

    globalMin = newGlobalMin;
}

void RLAPSolver::solve(const Tensor<int>& minRowValues){
    minimizeRowsAndCols(minRowValues);
    coverZeros();
    int globalMin = 0;
    minimizeRemaining(globalMin);

}
