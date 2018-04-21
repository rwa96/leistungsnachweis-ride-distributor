#ifndef OUTPUT_DATA_TEST_H
#define OUTPUT_DATA_TEST_H

#include <string>
#include <gtest/gtest.h>

class OutputDataTest: public ::testing::Test {
protected:
    OutputDataTest();
    virtual void TearDown();
    std::string getOutputFileContent();
    std::string outputFile;
};

#endif // OUTPUT_DATA_TEST_H
