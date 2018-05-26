#ifndef RLAP_SOLVER_TEST_H
#define RLAP_SOLVER_TEST_H

#include <list>
#include <functional>
#include <memory>
#include <gtest/gtest.h>
#include "RLAPSolver.hpp"

struct RLAP {
    Tensor<int> inputMatrix;
    int expectedSum;
};


class RLAPSolverTest: public ::testing::TestWithParam<RLAP> {
protected:
    using SolverCreator = std::function<RLAPSolver*(const Tensor<int>&)>;

    int assignmentSum(const Tensor<unsigned>& assignments, const Tensor<int>& inputMatrix);
    void uniqueEntries(const Tensor<unsigned>& assignments, unsigned& uniqueRows,
                       unsigned& uniqueCols);
    RLAPSolverTest();

    std::list<SolverCreator> solvers;
};

#endif // RLAP_SOLVER_TEST_H
