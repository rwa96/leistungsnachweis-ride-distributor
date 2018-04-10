#include <fstream>
#include "InputDataTest.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem::v1;
#else
	#include <filesystem>
	namespace fs = std::filesystem;
#endif

InputDataTest::InputDataTest() :exampleInputString(
	"3 4 2 3 2 10 \n"
	"0 0 1 3 2 9 \n"
	"1 2 1 0 0 9 \n"
	"2 0 2 2 0 9 \n") {};

void InputDataTest::SetUp() {
	inputFile = fs::temp_directory_path().string() + "inputFile";
	std::fstream outFile;
	outFile.exceptions(std::fstream::failbit | std::fstream::badbit);

	outFile.open(inputFile, std::fstream::out);
	outFile << exampleInputString;
};

void InputDataTest::TearDown() {
	fs::remove(inputFile);
};

TEST(InputDataTest, memberVariables) {
	const InputData exampleInputData(inputFile);
	EXPECT_EQ(exampleInputData.cols, 3);
	EXPECT_EQ(exampleInputData.rows, 4);
	EXPECT_EQ(exampleInputData.fleetSize, 2);
	EXPECT_EQ(exampleInputData.nRides, 3);
	EXPECT_EQ(exampleInputData.bonus, 2);
	EXPECT_EQ(exampleInputData.maxTime, 10);

	EXPECT_THAT(exampleInputData.startX, ::testing::ContainerEq({ 0, 1, 2 }));
	EXPECT_THAT(exampleInputData.startY, ::testing::ContainerEq({ 0, 1, 2 });
	EXPECT_THAT(exampleInputData.endX, ::testing::ContainerEq({ 1, 1, 2 });
	EXPECT_THAT(exampleInputData.endY, ::testing::ContainerEq({ 3, 0, 2 });
	EXPECT_THAT(exampleInputData.startT, ::testing::ContainerEq({ 2, 0, 0 });
	EXPECT_THAT(exampleInputData.endT, ::testing::ContainerEq({ 9, 9, 9 });
};

TEST(InputDataTest, stringOutput) {
	const InputData exampleInputData(inputFile);
	EXPECT_EQ(exampleInputData.str(), exampleInputString);
};

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
};
