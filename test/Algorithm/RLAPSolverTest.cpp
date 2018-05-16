#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "RLAPSolver.hpp"


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
