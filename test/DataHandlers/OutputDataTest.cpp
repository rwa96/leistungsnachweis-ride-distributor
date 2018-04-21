#include <fstream>
#include <stdio.h>
#include "OutputDataTest.hpp"
#include "OutputData.hpp"

OutputDataTest::OutputDataTest(): outputFile("testFile.out") {};

void OutputDataTest::TearDown() {
    remove(outputFile.c_str());
}

std::string OutputDataTest::getOutputFileContent() {
    std::fstream inFile;
    inFile.exceptions(std::fstream::failbit | std::fstream::badbit);
    inFile.open(outputFile, std::fstream::in);
    return std::string(std::istreambuf_iterator<char>(inFile),
                       std::istreambuf_iterator<char>());
}

TEST_F(OutputDataTest, CheckParent) {
    const OutputData noParent(std::shared_ptr<OutputData>(),
                              std::unique_ptr<Tensor<unsigned>> value);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
};
