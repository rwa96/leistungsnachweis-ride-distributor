#include "RLAPSolverTest.hpp"
#include "RLAPSolverHungarian.hpp"

RLAPSolverTest::RLAPSolverTest(){
    solvers.push_back([](Tensor<int>& m) -> std::unique_ptr<RLAPSolver> {
        Tensor<int> minRowValues({m.getDims()[0]}, 0);
        int maxEntry = 0;
        for(unsigned row = 0; row < m.getDims()[0]; ++row){
            for(unsigned col = 0; col < m.getDims()[1]; ++col){
                const int entry = m(row, col);
                if(minRowValues(row) == 0 || entry < minRowValues(row)){
                    minRowValues(row) = entry;
                }
                if(entry > maxEntry){
                    maxEntry = entry;
                }
            }
        }
        return std::make_unique<RLAPSolverHungarian>(m, minRowValues, maxEntry);
    });
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
