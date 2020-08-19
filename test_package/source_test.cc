#include <gtest/gtest.h>
//#include "source.h"


class UnitTestTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
};

TEST_F(UnitTestTest, unitTestTrue) {
    //EXPECT_TRUE(unit_test(true));
	EXPECT_TRUE(true);
}

TEST_F(UnitTestTest, unitTestFalse) {
    //EXPECT_FALSE(unit_test(false));
	EXPECT_FALSE(false);
}
