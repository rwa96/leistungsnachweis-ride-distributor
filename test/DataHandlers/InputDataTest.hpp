#ifndef INPUT_DATA_TEST_H
#define INPUT_DATA_TEST_H

#include <gtest/gtest.h>
#include "InputData.hpp"

class InputDataTest: public ::testing::Test {
    InputDataTest();
    virtual ~InputDataTest();
    virtual void SetUp();
    virtual void TearDown();
};

#endif // INPUT_DATA_TEST_H
