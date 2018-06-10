#ifndef INPUT_DATA_TEST_H
#define INPUT_DATA_TEST_H

#include <string>
#include <gtest/gtest.h>
#include "Algorithm.hpp"

class AlgorithmTest : public ::testing::Test {
protected:
	AlgorithmTest();
    virtual void SetUp();
    virtual void TearDown();

    std::string exampleInputString;
    std::string exampleInputFile;

	std::string exampleOutputFile;

	std::string expectedOutputString;
	std::string expectedOutputFile;
};

#endif // INPUT_DATA_TEST_H
