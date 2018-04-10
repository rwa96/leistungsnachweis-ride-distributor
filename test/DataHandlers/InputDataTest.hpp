#ifndef INPUT_DATA_TEST_H
#define INPUT_DATA_TEST_H

#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "InputData.hpp"

class InputDataTest: public ::testing::Test {
public:
	InputDataTest();
    void SetUp();
    void TearDown();
private:
	std::string exampleInputString;
	std::string inputFile;
};

#endif // INPUT_DATA_TEST_H
