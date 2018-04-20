#ifndef INPUT_DATA_TEST_H
#define INPUT_DATA_TEST_H

#include <string>
#include <gtest/gtest.h>
#include "InputData.hpp"

class InputDataTest: public ::testing::Test {
protected:
	InputDataTest();
    virtual void SetUp();
    virtual void TearDown();
	std::string exampleInputString;
	std::string inputFile;
	std::string noneExistingInputFile;
	std::string invalidInputFile;
};

#endif // INPUT_DATA_TEST_H
