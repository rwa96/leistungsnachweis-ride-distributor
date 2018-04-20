#include <fstream>
#include <stdio.h>
#include "InputDataTest.hpp"

InputDataTest::InputDataTest() :
	exampleInputString(
		"3 4 2 3 2 10 \n"
		"0 0 1 3 2 9 \n"
		"1 2 1 0 0 9 \n"
		"2 0 2 2 0 9 \n"),
	noneExistingInputFile("") {};

void InputDataTest::SetUp() {
	inputFile = "testInputFile.in";
	invalidInputFile = "testInvalidInputFile.in";
	std::fstream outFile;
	
	outFile.exceptions(std::fstream::failbit | std::fstream::badbit);
	outFile.open(inputFile, std::fstream::out);
	outFile << exampleInputString;
	outFile.close();

	outFile.open(invalidInputFile, std::fstream::out);
	outFile << "invalid input";
};

void InputDataTest::TearDown() {
    remove(inputFile.c_str());
	remove(invalidInputFile.c_str());
};

TEST_F(InputDataTest, invalidFile) {
	ASSERT_THROW(InputData::genFromFile(""), std::fstream::failure);
	ASSERT_ANY_THROW(InputData::genFromFile(invalidInputFile));
}

TEST_F(InputDataTest, memberVariables) {
	const InputData exampleInputData = *InputData::genFromFile(inputFile);
    EXPECT_EQ(exampleInputData.rows, 3);
	EXPECT_EQ(exampleInputData.cols, 4);
	EXPECT_EQ(exampleInputData.fleetSize, 2);
	EXPECT_EQ(exampleInputData.nRides, 3);
	EXPECT_EQ(exampleInputData.bonus, 2);
	EXPECT_EQ(exampleInputData.maxTime, 10);
};

TEST_F(InputDataTest, stringOutput) {
	const InputData exampleInputData = *InputData::genFromFile(inputFile);
    const std::string expectedOutput =
        "number of rides: 3\n"
        "map: (3, 4)\n"
        "number of cars: 2\n"
        "bonus: 2\n"
        "simulation steps: 10\n";
	EXPECT_EQ(exampleInputData.str(), expectedOutput);
};

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
};
