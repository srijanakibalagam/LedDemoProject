#include <gtest/gtest.h>

#include "../src/led.h"
#include "../src/run_led.h"

int count_on = 0;
int count_off = 0;

CLed::CLed() {}
void CLed::SetFileName(std::string filename) {}
int  CLed::Write( unsigned int value )
{
	if( value == 255 )
		count_on++;
	else if ( value == 0 )
		count_off++;
	else {}

	return 0;
}

class UnitTestTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
};

TEST_F(UnitTestTest, unitTestFalse) {
	EXPECT_FALSE(run_led());
	EXPECT_EQ( 3, count_on );
	EXPECT_EQ( 3, count_off );
}
