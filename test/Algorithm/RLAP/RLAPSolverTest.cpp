#include <unordered_set>
#include "RLAPSolverTest.hpp"
#include "RLAPSolverHungarian.hpp"

RLAPSolverTest::RLAPSolverTest() {
    /*solvers.push_back([](const Tensor<int>& m) -> RLAPSolver* {
        return new RLAPSolverHungarian(m, minRowValues, maxEntry);
    });*/
}

void RLAPSolverTest::uniqueEntries(const Tensor<int>& assignments, unsigned& uniqueRows,
                                   unsigned& uniqueCols) {
    std::unordered_set<int> rowSet, colSet;

    for(unsigned i = 0; i < assignments.getDims()[0]; ++i) {
        rowSet.insert(assignments(i, 0));
        colSet.insert(assignments(i, 1));
    }

    uniqueRows = rowSet.size();
    uniqueCols = colSet.size();
}

int RLAPSolverTest::assignmentSum(const Tensor<int>& assignments,
                                  const Tensor<int>& inputMatrix) {
    int result = 0;

    for(unsigned row = 0; row < assignments.getDims()[0]; ++row) {
        result += inputMatrix(assignments(row, 0), assignments(row, 1));
    }

    return result;
}

std::list<RLAP> testParams = {
    {Tensor<int>({2, 3}, 1), 2},
    {Tensor<int>({3, 2}, 1), 2}
};

INSTANTIATE_TEST_CASE_P(RLAPTestCases, RLAPSolverTest, ::testing::ValuesIn(testParams));

TEST_P(RLAPSolverTest, TestingWithRLAPParams) {
    const RLAP& param = GetParam();
    const Tensor<int>& inputMatrix = param.inputMatrix;
    const unsigned nAssignments = std::min(inputMatrix.getDims()[0],
                                           inputMatrix.getDims()[1]);
    int expectedSum = param.expectedSum;

    for(SolverCreator sc : solvers) {
        std::unique_ptr<RLAPSolver> solver(sc(param.inputMatrix));
        Tensor<int> assignments({nAssignments, 2}, 0);

        solver->solve(assignments);
        unsigned uniqueRows, uniqueCols;
        uniqueEntries(assignments, uniqueRows, uniqueCols);

        EXPECT_EQ(nAssignments, uniqueRows);
        EXPECT_EQ(nAssignments, uniqueCols);
        EXPECT_EQ(expectedSum, assignmentSum(assignments, inputMatrix));
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
