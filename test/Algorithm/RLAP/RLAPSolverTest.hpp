#ifndef RLAP_SOLVER_TEST_H
#define RLAP_SOLVER_TEST_H

#include <list>
#include <functional>
#include <gtest/gtest.h>
#include <memory>
#include "RLAPSolver.hpp"

class RLAPSolverTest: public ::testing::Test {
protected:
    using SolverCreator = std::function<std::unique_ptr<RLAPSolver>(Tensor<int>&)>;
    RLAPSolverTest();
    std::list<SolverCreator> solvers;
};

#endif // RLAP_SOLVER_TEST_H
