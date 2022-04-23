/*
 * led.h
 *
 * Created: 20/02/2022 11.12.37
 */ 

#ifndef LED_H_
#define LED_H_

#define ON 1
#define OFF 0

void init_leds();
void set_led(uint8_t led_no, uint8_t state);
void lightbar(uint8_t level);

#endif /* LED_H_ */