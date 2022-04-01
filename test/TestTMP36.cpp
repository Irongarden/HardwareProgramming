#include "gtest/gtest.h"

extern "C"
{
#include <avr/io.h>
#include "tmp36.h"
#include <stdint.h>

	void ISR_ADC_vect();
}

class TMP36 : public ::testing::Test
{

protected:
	void SetUp()
	{
		tmp36_init(0);
	}

	void TearDown()
	{

	}
};

TEST_F(TMP36, set_pk7_input) {
	uint8_t state = DDRK & _BV(PK7);

	EXPECT_EQ(0, state);
}

TEST_F(TMP36, set_pg0_output) {
	uint8_t state = DDRG & _BV(PG0);

	EXPECT_EQ(1, state);
}

TEST_F(TMP36, set_ADMUX) {
	EXPECT_EQ(0x47, ADMUX);
}

TEST_F(TMP36, set_ADCSRB) {
	EXPECT_EQ(0xD, ADCSRB);
}

TEST_F(TMP36, set_ADCSRA) {
	EXPECT_EQ(0xEE, ADCSRA);
}

TEST_F(TMP36, set_TCCR1A) {
	EXPECT_EQ(0x12, TCCR1A);
}

TEST_F(TMP36, set_TCCR1B) {
	EXPECT_EQ(0x4, TCCR1B);
}

TEST_F(TMP36, set_TIMSK1) {
	EXPECT_EQ(0x4, TIMSK1);
}

TEST_F(TMP36, set_OCR1B) {
	EXPECT_EQ(0x7A11, OCR1B);
}

TEST_F(TMP36, enable_tmp36_PG0_high) {
	uint8_t state = PORTG & _BV(PG0);
	EXPECT_EQ(1, state);
}

TEST_F(TMP36, adc_started) {
	EXPECT_EQ(0xEE, ADCSRA);
}

TEST_F(TMP36, mv_to_temp) {
	int mv = 660;
	for (int i = 16; i < 27; i++)
	{
		int temp = mv_to_c(mv);
		EXPECT_EQ(i, temp);
		mv += 10;
	}
}
TEST_F(TMP36, adc0_to_mv) {
	EXPECT_EQ(0, adc_to_mv(0));
}

TEST_F(TMP36, adc140_to_mv) {
	EXPECT_EQ(684, adc_to_mv(140));
}

TEST_F(TMP36, adc145_to_mv) {
	EXPECT_EQ(708, adc_to_mv(145));
}
TEST_F(TMP36, adc155_to_mv) {
	EXPECT_EQ(757, adc_to_mv(155));
}