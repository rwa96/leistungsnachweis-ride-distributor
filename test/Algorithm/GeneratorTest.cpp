#include "GeneratorTest.hpp"

TEST(GeneratorTest, EmptyInitialization) {
    /*InputData inputData;
    unsigned nTries, kBest;
    Generator sut(inputData, nTries, unsigned kBest);*/
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
};
