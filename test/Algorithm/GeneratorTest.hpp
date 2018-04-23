#ifndef GENERATOR_TEST_H
#define GENERATOR_TEST_H

#include <gtest/gtest.h>


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
};

#endif
