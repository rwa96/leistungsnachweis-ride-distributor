#include <unordered_set>
#include <numeric>
#include <stdexcept>
#include "RLAPSolverHungarian.hpp"

#ifndef NDEBUG
    #include <iostream>

    #define DBG_PRINT_ZEROS(v) std::cout << "zeros" << std::endl; \
    for(auto elm: v) \
        std::cout << '[' << elm.row \
        << ", " << elm.col << \
        ", " << elm.deleted << ']' << std::endl
#else
    #define DBG_PRINT_ZEROS(_)
#endif

#define MAX_DIM(m) std::max(m.getDims()[0], m.getDims()[1])

RLAPSolverHungarian::RLAPSolverHungarian(const Tensor<int>& mat, const int maxCost):
    rows(mat.getDims()[0]),
    cols(mat.getDims()[1]),
    size(MAX_DIM(mat)),
    costMat({MAX_DIM(mat), MAX_DIM(mat)}),
    rowMin({MAX_DIM(mat)}, maxCost),
    colMin({MAX_DIM(mat)}, maxCost),
    solved(false)
{
    int newMaxCost = 0;
    for(unsigned row = 0; row < rows; ++row){
        for(unsigned col = 0; col < cols; ++col) {
            int& entry = costMat(row, col);
            entry = maxCost - mat(row, col);

            if(rowMin(row) > entry){
                rowMin(row) = entry;
            }
            if(colMin(col) > entry){
                colMin(col) = entry;
            }
            if(newMaxCost < entry){
                newMaxCost = entry;
            }
        }
    }

    if(rows != cols) {
        unsigned rowStart, colStart;

        if(rows > cols){
            rowStart = 0;
            colStart = cols;
            for(unsigned col = colStart; col < size; ++col){colMin(col) = newMaxCost;}
        }else{
            rowStart = rows;
            colStart = 0;
            for(unsigned row = rowStart; row < size; ++row){rowMin(row) = newMaxCost;}
        }

        for(unsigned row = rowStart; row < size; ++row) {
            for(unsigned col = colStart; col < size; ++col) {
                costMat(row, col) = newMaxCost;
            }
        }
    }
}


void RLAPSolverHungarian::reduceRowsAndCols(Tensor<unsigned>& zeroCountRows, Tensor<unsigned>& zeroCountCols){
    std::unordered_set<unsigned> nonZeroCols;
    for(unsigned i = 0; i < size; ++i){
        zeroCountCols(i) = 0;
        zeroCountRows(i) = 0;
        nonZeroCols.insert(i);
    }

    // Reduce rows
    for(unsigned row = 0; row < size; ++row){
        for(unsigned col = 0; col < size; ++col){
            int& entry = costMat(row, col);
            entry -= rowMin(row);
            if(entry == 0){
                nonZeroCols.erase(col);
                ++zeroCountCols(col);
                ++zeroCountRows(row);
                zeros.push_back({row, col, false});
            }else if(colMin(col) > entry){
                colMin(col) = entry;
            }
        }
    }

    // Reduce non zero columns
    for(unsigned col: nonZeroCols){
        for(unsigned row = 0; row < size; ++row){
            costMat(row, col) -= colMin(col);
            if(costMat(row, col) == 0){
                ++zeroCountCols(col);
                ++zeroCountRows(row);
                zeros.push_back({row, col, false});
            }
        }
    }
}

unsigned RLAPSolverHungarian::coverZeros(Tensor<unsigned>& zeroCountRows, Tensor<unsigned>& zeroCountCols, Tensor<bool>& rowLines, Tensor<bool>& colLines){
    Tensor<bool> zeroCountRowsFlag({size}), zeroCountColsFlag({size});
    bool changedMarker = true;
    bool changed = !changedMarker;
    unsigned lineCount = 0;

    for(unsigned i = 0; i < size; ++i){
        rowLines(i) = false;
        colLines(i) = false;
        zeroCountRowsFlag(i) = false;
        zeroCountColsFlag(i) = false;
    }

    do{
        for(unsigned i = 0; i < zeros.size(); ++i){
            if(zeros[i].deleted){continue;}
            unsigned currentRow = zeros[i].row;
            unsigned currentCol = zeros[i].col;

            if(zeroCountRows(currentRow) > zeroCountCols(currentCol)){
                for(unsigned j = 0; j < zeros.size(); ++j){
                    if(zeros[j].deleted){continue;}
                    else if(zeros[j].row == currentRow){
                        --zeroCountCols(zeros[j].col);
                        zeros[j].deleted = true;
                        if(zeroCountColsFlag(zeros[j].col) == changedMarker){
                            changed = true;
                        }
                    }
                }

                ++lineCount;
                rowLines(currentRow) = true;

                zeroCountRows(currentRow) = 0;
                if(zeroCountRowsFlag(currentRow) == changedMarker){
                    changed = true;
                }
            }else if (zeroCountRows(currentRow) < zeroCountCols(currentCol)){
                for(unsigned j = 0; j < zeros.size(); ++j){
                    if(zeros[j].deleted){continue;}
                    else if(zeros[j].col == currentCol){
                        --zeroCountRows(zeros[j].row);
                        zeros[j].deleted = true;
                        if(zeroCountRowsFlag(zeros[j].row) == changedMarker){
                            changed = true;
                        }
                    }
                }

                ++lineCount;
                colLines(currentCol) = true;

                zeroCountCols(currentCol) = 0;
                if(zeroCountColsFlag(currentCol) == changedMarker){
                    changed = true;
                }
            }else{
                zeroCountRowsFlag(currentRow) = changedMarker;
                zeroCountColsFlag(currentCol) = changedMarker;
            }
        }

        changedMarker = !changedMarker;
    }while(changed);

    for(unsigned i = 0; i < zeros.size(); ++i){
        if(!zeros[i].deleted){
            if(!rowLines(zeros[i].row)){
                ++lineCount;
                rowLines(zeros[i].row) = true;
            }
        }
    }

    return lineCount;
}

int RLAPSolverHungarian::recalculateCosts(const int minVal, Tensor<unsigned>& zeroCountRows, Tensor<unsigned>& zeroCountCols, Tensor<bool>& rowLines, Tensor<bool>& colLines){
    int newMinVal = minVal;

    if(newMinVal == 0){
        for(unsigned row = 0; row < size; ++row){
            zeroCountRows(row) = 0;
            for(unsigned col = 0; col < size; ++col){
                zeroCountCols(col) = 0;
                if(colLines(col)){continue;}
                else if(newMinVal == 0 || newMinVal > costMat(row, col)){
                    newMinVal = costMat(row, col);
                }
            }
        }
    }

    for(unsigned row = 0; row < size; ++row){
        for(unsigned col = 0; col < size; ++col){
            int& entry = costMat(row, col);

            if(rowLines(row) && colLines(col)){
                entry += minVal;
            }else if(!rowLines(row) && !colLines(col)){
                entry -= minVal;
            }

            if(entry == 0){
                ++zeroCountRows(row);
                ++zeroCountCols(col);
                zeros.push_back({row, col, false});
            }else if(newMinVal > entry){
                newMinVal = entry;
            }
        }
    }

    return newMinVal;
}

void RLAPSolverHungarian::assignMatching(Tensor<int>& assignments){
    Tensor<bool> assignedRows({rows}, false), assignedCols({cols}, false);
    const unsigned maxAssignments = std::min(rows, cols);
    unsigned assignmentsInd = 0;
    for(Zero elm: zeros){
        if(elm.row < rows && elm.col < cols
            && !assignedRows(elm.row) && !assignedCols(elm.col))
        {
            assignments(assignmentsInd, 0) = elm.row;
            assignments(assignmentsInd, 1) = elm.col;
            assignedRows(elm.row) = true;
            assignedCols(elm.col) = true;
            if(++assignmentsInd >= maxAssignments){break;}
        }
    }
}

void RLAPSolverHungarian::solve(Tensor<int>& assignments){
    if(solved){throw std::runtime_error("RLAP solved already");}

    Tensor<unsigned> zeroCountRows({size}), zeroCountCols({size});
    Tensor<bool> rowLines({size}), colLines({size});

    reduceRowsAndCols(zeroCountRows, zeroCountCols);
    unsigned lineCount = coverZeros(zeroCountRows, zeroCountCols, rowLines, colLines);

    int minVal = 0;
    while(lineCount < size){
        zeros.clear();
        minVal = recalculateCosts(minVal, zeroCountRows, zeroCountCols, rowLines, colLines);
        lineCount = coverZeros(zeroCountRows, zeroCountCols, rowLines, colLines);
    }

    assignMatching(assignments);
    solved = true;
}
