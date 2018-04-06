#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Tensor.hpp"

TEST(TensorTest, EmptyInitiation){
    const Tensor empty;
    EXPECT_EQ(empty.getSize(), 0);
    EXPECT_TRUE(empty.getDims().empty());

    const Tensor singleDimEmpty({0});
    EXPECT_EQ(singleDimEmpty.getSize(), 0);
    EXPECT_TRUE(singleDimEmpty.getDims().empty());

    const Tensor twoDimEmpty({0, 0});
    EXPECT_EQ(twoDimEmpty.getSize(), 0);
    EXPECT_TRUE(twoDimEmpty.getDims().empty());

    const Tensor threeDimEmpty({0,0,0});
    EXPECT_EQ(threeDimEmpty.getSize(), 0);
    EXPECT_TRUE(threeDimEmpty.getDims().empty());
}

TEST(TensorTest, RandomValueInitialization){
    const unsigned randomValue = 42;

    const Tensor singleDim({randomValue});
    EXPECT_EQ(singleDim.getSize(), randomValue);
    EXPECT_THAT(singleDim.getDims(), ::testing::ContainerEq(std::vector<unsigned>(1, randomValue)));

    const Tensor twoDim({randomValue, randomValue});
    EXPECT_EQ(twoDim.getSize(), randomValue*randomValue);
    EXPECT_THAT(twoDim.getDims(), ::testing::ContainerEq(std::vector<unsigned>(2, randomValue)));

    const Tensor threeDim({randomValue, randomValue, randomValue});
    EXPECT_EQ(threeDim.getSize(), randomValue*randomValue*randomValue);
    EXPECT_THAT(threeDim.getDims(), ::testing::ContainerEq(std::vector<unsigned>(3, randomValue)));
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
