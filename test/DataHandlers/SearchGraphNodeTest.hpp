#ifndef SEARCH_GRAPH_NODE_TEST_H
#define SEARCH_GRAPH_NODE_TEST_H

#include <string>
#include <gtest/gtest.h>

class SearchGraphNodeTest: public ::testing::Test {
protected:
    SearchGraphNodeTest();
    virtual void TearDown();
    std::string getOutputFileContent();
    std::string outputFile;
};

#endif // SEARCH_GRAPH_NODE_TEST_H
