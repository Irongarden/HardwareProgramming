#include "gtest/gtest.h"
#include <math.h>

extern "C"
{
	#include <avr/io.h>
	#include "led.h"

}

class LEDDriver : public ::testing::Test
{
protected:
	void SetUp()
	{
		init_leds();
	}
	void TearDown()
	{

	}
};

TEST_F(LEDDriver, PortA_set_as_output) {
  EXPECT_EQ(0xFF, DDRA);
}

TEST_F(LEDDriver, leds_off) {
	EXPECT_EQ(0xFF, PORTA);
}

TEST_F(LEDDriver, led1_on)
{
	EXPECT_EQ(0xFF, PORTA);

	set_led(1, ON);
	EXPECT_EQ(0xFE, PORTA);
}

TEST_F(LEDDriver, led1_on_on)
{
	EXPECT_EQ(0xFF, PORTA);

	set_led(1, ON);
	EXPECT_EQ(0xFE, PORTA);
	
	set_led(1, ON);
	EXPECT_EQ(0xFE, PORTA);
}

TEST_F(LEDDriver, led1_on_off)
{
	EXPECT_EQ(0xFF, PORTA);

	set_led(1, ON);
	EXPECT_EQ(0xFE, PORTA);

	set_led(1, OFF);
	EXPECT_EQ(0xFF, PORTA);
}

TEST_F(LEDDriver, led8_on)
{
	EXPECT_EQ(0xFF, PORTA);

	set_led(8, ON);
	EXPECT_EQ(0x7F, PORTA);
}

TEST_F(LEDDriver, led8_on_off)
{
	EXPECT_EQ(0xFF, PORTA);

	set_led(8, ON);
	EXPECT_EQ(0x7F, PORTA);

	set_led(8, OFF);
	EXPECT_EQ(0xFF, PORTA);
}

TEST_F(LEDDriver, led2_on_led6_on_led2_off_led6_off)
{
	EXPECT_EQ(0xFF, PORTA);

	set_led(2, ON);
	EXPECT_EQ(0xFD, PORTA);

	set_led(6, ON);
	EXPECT_EQ(0xDD, PORTA);

	set_led(2, OFF);
	EXPECT_EQ(0xDF, PORTA);

	set_led(6, OFF);
	EXPECT_EQ(0xFF, PORTA);
}

TEST_F(LEDDriver, lightbar)
{
	for (uint8_t i = 0; i < 9; i++)
	{
		lightbar(i);
		uint8_t expected = (255 - pow(2, i)) + 1;
		EXPECT_EQ(expected, PORTA);
	}
}