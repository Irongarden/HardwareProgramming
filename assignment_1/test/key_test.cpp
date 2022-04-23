#include "gtest/gtest.h"

extern "C"
{
#include <avr/io.h>
#include "key.h"

}

class KeyDriver : public ::testing::Test
{
protected:
	void SetUp()
	{
		init_keys();
	}
	void TearDown()
	{

	}
};

/*
* Testing Data Direction PORT C.
*/
TEST_F(KeyDriver, PC0_set_as_input) {
	uint8_t DDPC0 = DDRC & _BV(PC0);

	EXPECT_EQ(0, DDPC0);
}

TEST_F(KeyDriver, PC1_set_as_input) {
	uint8_t DDPC1 = DDRC & _BV(PC0);

	EXPECT_EQ(0, DDPC1);
}

TEST_F(KeyDriver, PC2_set_as_input) {
	uint8_t DDPC2 = DDRC & _BV(PC2);

	EXPECT_EQ(0, DDPC2);
}

TEST_F(KeyDriver, PC3_set_as_input) {
	uint8_t DDPC3 = DDRC & _BV(PC3);

	EXPECT_EQ(0, DDPC3);
}

TEST_F(KeyDriver, PC4_set_as_input) {
	uint8_t DDPC4 = DDRC & _BV(PC4);

	EXPECT_EQ(0, DDPC4);
}

TEST_F(KeyDriver, PC5_set_as_input) {
	uint8_t DDPC5 = DDRC & _BV(PC5);

	EXPECT_EQ(0, DDPC5);
}

/*
* Testing Pull Up State PORT C.
*/
TEST_F(KeyDriver, PC0_set_pull_up) {
	uint8_t portC0 = PORTC & _BV(PC0);

	EXPECT_EQ(1, portC0);
}

TEST_F(KeyDriver, PC1_set_pull_up) {
	uint8_t portC1 = PORTC & _BV(PC1);

	EXPECT_EQ(2, portC1);
}

TEST_F(KeyDriver, PC2_set_pull_up) {
	uint8_t portC2 = PORTC & _BV(PC2);

	EXPECT_EQ(4, portC2);
}

TEST_F(KeyDriver, PC3_set_pull_up) {
	uint8_t portC3 = PORTC & _BV(PC3);

	EXPECT_EQ(8, portC3);
}

TEST_F(KeyDriver, PC4_set_pull_up) {
	uint8_t portC4 = PORTC & _BV(PC4);

	EXPECT_EQ(16, portC4);
}

TEST_F(KeyDriver, PC5_set_pull_up) {
	uint8_t portC5 = PORTC & _BV(PC5);

	EXPECT_EQ(32, portC5);
}

/*
* Testing Pull Up State PORT D.
*/
TEST_F(KeyDriver, PD2_set_pull_up) {
	uint8_t portD2 = PORTD & _BV(PD2);

	EXPECT_EQ(4, portD2);
}

TEST_F(KeyDriver, PD3_set_pull_up) {
	uint8_t portD3 = PORTD & _BV(PD3);

	EXPECT_EQ(8, portD3);
}

/*
* Testing Data Direction PORT D.
*/
TEST_F(KeyDriver, PD2_set_as_input) {
	uint8_t DDPD2 = DDRD & _BV(PD2);

	EXPECT_EQ(0, DDPD2);
}

TEST_F(KeyDriver, PD3_set_as_input) {
	uint8_t DDPD3 = DDRD & _BV(PD3);

	EXPECT_EQ(0, DDPD3);
}