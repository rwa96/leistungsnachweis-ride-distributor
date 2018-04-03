#ifndef UTILS_TEST_H
#define UTILS_TEST_H

#include <gtest/gtest.h>
#include "Utils.hpp"

class UtilsTest: public ::testing::Test {
    InputDataTest();
    virtual ~InputDataTest();
    virtual void SetUp();
    virtual void TearDown();
};

#endif // UTILS_TEST_H
