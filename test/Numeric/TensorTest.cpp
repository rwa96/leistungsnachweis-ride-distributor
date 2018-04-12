#include <vector>
#include <gmock/gmock.h>
#include "Tensor.hpp"

TEST(TensorTest, EmptyInitiation){
    const Tensor<int> empty;
    EXPECT_EQ(empty.getSize(), 0);
    EXPECT_TRUE(empty.getDims().empty());

    const Tensor<int> singleDimEmpty({0});
    EXPECT_EQ(singleDimEmpty.getSize(), 0);
    EXPECT_TRUE(singleDimEmpty.getDims().empty());

    const Tensor<int> twoDimEmpty({0, 0});
    EXPECT_EQ(twoDimEmpty.getSize(), 0);
    EXPECT_TRUE(twoDimEmpty.getDims().empty());

    const Tensor<int> threeDimEmpty({0,0,0});
    EXPECT_EQ(threeDimEmpty.getSize(), 0);
    EXPECT_TRUE(threeDimEmpty.getDims().empty());
}

TEST(TensorTest, RandomValueInitialization){
    const unsigned randomValue = 42;

    const Tensor<int> singleDim({randomValue});
    EXPECT_EQ(singleDim.getSize(), randomValue);
    EXPECT_THAT(singleDim.getDims(), ::testing::ContainerEq(std::vector<unsigned>(1, randomValue)));

    const Tensor<int> twoDim({randomValue, randomValue});
    EXPECT_EQ(twoDim.getSize(), randomValue*randomValue);
    EXPECT_THAT(twoDim.getDims(), ::testing::ContainerEq(std::vector<unsigned>(2, randomValue)));

    const Tensor<int> threeDim({randomValue, randomValue, randomValue});
    EXPECT_EQ(threeDim.getSize(), randomValue*randomValue*randomValue);
    EXPECT_THAT(threeDim.getDims(), ::testing::ContainerEq(std::vector<unsigned>(3, randomValue)));
}

TEST(TensorTest, 2DIndexAccess) {
	Tensor<int> threeDim({ 2, 2 });
	for (unsigned listIndex = 0; listIndex < threeDim.getSize(); ++listIndex) {
		threeDim(listIndex) = listIndex;
	}

	unsigned listIndex = 0;
	for (unsigned x = 0; x < threeDim.getDims()[0]; ++x) {
		for (unsigned y = 0; y < threeDim.getDims()[1]; ++y) {
			EXPECT_EQ(threeDim(x, y), listIndex++);
		}
	}
}

TEST (TensorTest, 3DIndexAccess) {
	Tensor<int> threeDim({ 2, 2, 2 });
	for (unsigned listIndex = 0; listIndex < threeDim.getSize(); ++listIndex) {
		threeDim(listIndex) = listIndex;
	}

	unsigned listIndex = 0;
	for (unsigned x = 0; x < threeDim.getDims()[0]; ++x) {
		for (unsigned y = 0; y < threeDim.getDims()[1]; ++y) {
			for (unsigned z = 0; z < threeDim.getDims()[2]; ++z) {
				EXPECT_EQ(threeDim(x, y, z), listIndex++);
			}
		}
	}
}

TEST(TensorTest, StringRepresenation) {
	Tensor<int> sample({4});
	for (unsigned listIndex = 0; listIndex < sample.getSize(); ++listIndex) {
		sample(listIndex) = listIndex;
	}

	EXPECT_EQ(sample.str(), "[0, 1, 2, 3]\n");
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
