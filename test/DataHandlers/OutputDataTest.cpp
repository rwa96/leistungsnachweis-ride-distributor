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

TEST_F(OutputDataTest, NoParent) {
    std::unique_ptr<Tensor<unsigned>> singleEntry(new Tensor<unsigned>());
    const OutputData noParent(singleEntry);
    noParent.writeToFile(outputFile, 1);

    EXPECT_EQ(getOutputFileContent(), "0 \n");
}

TEST_F(OutputDataTest, Parent) {
    std::unique_ptr<Tensor<unsigned>> entries1(new Tensor<unsigned>({1, 2}, {0, 0}));
    std::unique_ptr<Tensor<unsigned>> entries2(new Tensor<unsigned>({1, 2}, {1, 1}));
    std::shared_ptr<OutputData> parent(new OutputData(entries1));
    OutputData sut(parent, entries2);

    sut.writeToFile(outputFile, 2);

    EXPECT_EQ(getOutputFileContent(), "1 0 \n1 1 \n");
}

TEST_F(OutputDataTest, MultipleCars) {
    std::unique_ptr<Tensor<unsigned>> multipleEntries(new Tensor<unsigned>({2, 2}, {0, 1, 2, 0}));
    const OutputData sut(multipleEntries);
    const unsigned fleetSize = 4;
    sut.writeToFile(outputFile, fleetSize);

    EXPECT_EQ(getOutputFileContent(), "1 1 \n0 \n1 0 \n0 \n");
}

TEST_F(OutputDataTest, multipleEntries) {
    std::unique_ptr<Tensor<unsigned>> entries1(new Tensor<unsigned>({1, 2}, {0, 0}));
    std::unique_ptr<Tensor<unsigned>> entries2(new Tensor<unsigned>({1, 2}, {0, 1}));
    std::shared_ptr<OutputData> parent(new OutputData(entries1));
    OutputData sut(parent, entries2);

    sut.writeToFile(outputFile, 1);

    EXPECT_EQ(getOutputFileContent(), "2 0 1 \n");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
};
