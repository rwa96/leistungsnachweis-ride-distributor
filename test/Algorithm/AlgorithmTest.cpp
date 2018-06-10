#include <fstream>
#include <stdio.h>
#include "AlgorithmTest.hpp"

AlgorithmTest::AlgorithmTest() :
	exampleInputString(
		"3 4 2 3 2 10\n"
		"0 0 1 3 2 9\n"
		"1 2 1 0 0 9\n"
		"2 0 2 2 0 9\n"),
	expectedOutputString(
		"2 0 1\n"
		"1 2\n"),
	exampleInputFile("testExampleFile.in"),
	exampleOutputFile("testExampleFile.out"),
	expectedOutputFile("testExpectedFile.out") {};

void AlgorithmTest::SetUp() {
	std::fstream file;
    file.exceptions(std::fstream::failbit | std::fstream::badbit);

    file.open(exampleInputFile, std::fstream::out);
    file << exampleInputString;
    file.close();

	file.open(expectedOutputFile, std::fstream::out);
	file << expectedOutputString;
	file.close();
};

void AlgorithmTest::TearDown() {
	remove(exampleInputFile.c_str());
	remove(expectedOutputFile.c_str());
};

/**
 * \test Checks if the algorithm produces expected results.
 */
TEST_F(AlgorithmTest, checkAlgorithm) {
    InputData exampleInputData = *InputData::genFromFile(exampleInputFile);
	Algorithm exampleAlgorithm(exampleInputData, exampleOutputFile);
	exampleAlgorithm.run();

	std::ifstream example(exampleOutputFile);
	std::stringstream exampleBuffer;
	exampleBuffer << example.rdbuf();

	std::ifstream expected(expectedOutputFile);
	std::stringstream expectedBuffer;
	expectedBuffer << expected.rdbuf();

    EXPECT_EQ(exampleBuffer.str(), expectedBuffer.str());
	remove(exampleOutputFile.c_str());
};

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
};
