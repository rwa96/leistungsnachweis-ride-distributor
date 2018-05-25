#include <unordered_set>
#include "Tensor.hpp"
#include "RLAPSolverTest.hpp"
#include "RLAPSolverHungarian.hpp"

RLAPSolverTest::RLAPSolverTest() {
    solvers.push_back([](const Tensor<int>& m) -> RLAPSolver* {
        int maxEntry = 0;
        for(unsigned row = 0; row < m.getDims()[0]; ++row){
            for(unsigned col = 0; col < m.getDims()[1]; ++col){
                if(maxEntry < m(row, col)){
                    maxEntry = m(row, col);
                }
            }
        }
        return new RLAPSolverHungarian(m, maxEntry);
    });
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
    {Tensor<int>({1, 1}, 42), 42},
    {Tensor<int>({2, 3}, 1), 2},
    {Tensor<int>({3, 2}, 1), 2},
    {Tensor<int>({1, 3}, {1, 2, 3}), 3},
    {Tensor<int>({3, 1}, {1, 2, 3}), 3},
    {Tensor<int>({3, 3}, {1, 1, 8, 19, 0, 9, 8, 13, 11}), 40},
    {Tensor<int>({4, 4}, {7, 9, 2, 13, 17, 5, 10, 4, 5, 12, 16, 15, 6, 18, 19, 6}), 64},
    {Tensor<int>({4, 6}, {1, 18, 15, 8, 18, 3, 19, 8, 12, 17, 8, 19, 13, 17, 11, 2, 17, 5, 6, 15, 12, 4, 8, 17}), 71},
    {Tensor<int>({6, 4}, {3, 15, 6, 0, 10, 19, 16, 18, 6, 16, 14, 9, 3, 8, 2, 18, 15, 14, 1, 17, 7, 6, 0, 4}), 66},
    {Tensor<int>({10, 10}, {
        18,  9, 12, 16, 18, 15, 14,  9, 18, 12,
        14, 16, 13, 13, 13, 17,  8, 11,  7, 14,
         6, 17, 10,  4, 11, 12,  3,  9,  8, 14,
         7,  4,  0,  3,  0,  8, 18, 10, 18, 17,
        16, 17,  6,  8, 13, 11,  8,  6, 15,  2,
         1, 18,  5, 17, 11,  3,  3,  8,  3,  4,
         6, 13, 19, 11, 18, 17, 11,  2,  4,  2,
        17, 13,  9, 11,  4,  5, 17, 10, 10, 12,
        17,  2, 15, 13, 13, 10,  5,  5, 17,  1,
         4,  6, 16, 17, 12, 18,  2,  8, 10,  9}), 167}
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
