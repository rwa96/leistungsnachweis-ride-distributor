#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Tensor.hpp"

/**
 * \test All possible inputs for Tensor#Tensor that will create
 *       an empty instance.
 */
TEST(TensorTest, EmptyInitialization) {
    const Tensor<int> empty;
    EXPECT_EQ(empty.getSize(), 0);
    EXPECT_TRUE(empty.getDims().empty());

    const Tensor<int> singleDimEmpty({0});
    EXPECT_EQ(singleDimEmpty.getSize(), 0);
    EXPECT_TRUE(singleDimEmpty.getDims().empty());

    const Tensor<int> twoDimEmpty({0, 0});
    EXPECT_EQ(twoDimEmpty.getSize(), 0);
    EXPECT_TRUE(twoDimEmpty.getDims().empty());

    const Tensor<int> threeDimEmpty({0, 0, 0});
    EXPECT_EQ(threeDimEmpty.getSize(), 0);
    EXPECT_TRUE(threeDimEmpty.getDims().empty());
}

/** \test Initialization of a 1D, 2D and 3D Tensor. */
TEST(TensorTest, DimensionsInitialization) {
    const unsigned sampleValue = 42;

    const Tensor<int> singleDim({sampleValue});
    EXPECT_EQ(singleDim.getSize(), sampleValue);
    EXPECT_THAT(singleDim.getDims(), ::testing::ContainerEq(std::vector<unsigned>(1,
                sampleValue)));

    const Tensor<int> twoDim({sampleValue, sampleValue});
    EXPECT_EQ(twoDim.getSize(), sampleValue * sampleValue);
    EXPECT_THAT(twoDim.getDims(), ::testing::ContainerEq(std::vector<unsigned>(2,
                sampleValue)));

    const Tensor<int> threeDim({sampleValue, sampleValue, sampleValue});
    EXPECT_EQ(threeDim.getSize(), sampleValue * sampleValue * sampleValue);
    EXPECT_THAT(threeDim.getDims(), ::testing::ContainerEq(std::vector<unsigned>(3,
                sampleValue)));
}

/** \test Checks the constructor that uses a value vector. */
TEST(TensorTest, ValueInitialization) {
    const std::vector<int> sampleValues = {1, 2, 3, 4, 5, 6, 7, 8};
    Tensor<int> sut({2, 2, 2}, sampleValues);

    auto sampleValueItr = sampleValues.begin();

    for(int i = 0; i < sut.getSize(); ++i) {
        EXPECT_EQ(sut(i), *sampleValueItr++);
    }
}

/** \test Success if copy constructor copys internal values correctly. */
TEST(TensorTest, CopyConstructor) {
    const std::vector<int> sampleValues = {1, 2, 3, 4, 5, 6, 7, 8};
    Tensor<int> sut1({2, 2, 2}, sampleValues);
    Tensor<int> sut2(sut1);

    EXPECT_THAT(sut1.getDims(), ::testing::ContainerEq(sut2.getDims()));
    EXPECT_EQ(sut1.getSize(), sut2.getSize());

    for(int i = 0; i < sut1.getSize(); ++i) {
        EXPECT_EQ(sut1(i), sut2(i));
    }
}

/** \test Checks if 2D index access works correctly. */
TEST(TensorTest, 2DIndexAccess) {
    Tensor<int> threeDim({ 2, 2 });

    for(unsigned listIndex = 0; listIndex < threeDim.getSize(); ++listIndex) {
        threeDim(listIndex) = listIndex;
    }

    unsigned listIndex = 0;

    for(unsigned row = 0; row < threeDim.getDims()[0]; ++row) {
        for(unsigned col = 0; col < threeDim.getDims()[1]; ++col) {
            EXPECT_EQ(threeDim(row, col), listIndex++);
        }
    }
}

/** \test Checks if 3D index access works correctly. */
TEST(TensorTest, 3DIndexAccess) {
    Tensor<int> threeDim({ 2, 2, 2 });

    for(unsigned listIndex = 0; listIndex < threeDim.getSize(); ++listIndex) {
        threeDim(listIndex) = listIndex;
    }

    unsigned listIndex = 0;

    for(unsigned row = 0; row < threeDim.getDims()[0]; ++row) {
        for(unsigned col = 0; col < threeDim.getDims()[1]; ++col) {
            for(unsigned height = 0; height < threeDim.getDims()[2]; ++height) {
                EXPECT_EQ(threeDim(row, col, height), listIndex++);
            }
        }
    }
}

/** \test Checks if Tensor#str works correctly. */
TEST(TensorTest, StringRepresenation) {
    Tensor<int> sample({4});

    for(unsigned listIndex = 0; listIndex < sample.getSize(); ++listIndex) {
        sample(listIndex) = listIndex;
    }

    EXPECT_EQ(sample.str(), "[0, 1, 2, 3]\n");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
