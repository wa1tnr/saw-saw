// Wed 18 Jul 23:10:29 UTC 2018
// main.cpp

// has working LED (as with D13) and working onboard NeoPixel

// previous timestamps:
// Wed 18 Jul 22:16:10 UTC 2018
// Tue 17 Jul 02:58:18 UTC 2018

/* Created: 7/17/2017 3:26:42 PM  * Author : deanm  */

/* Many changes: by wa1tnr, July 2018 */

#include "sam.h"
#include "local_board_init.h"
#include "PinMap_local.h"
#include "bsp_gpio.h"
#include "bsp_neopix.h"

void uSec(void) {
    for (volatile int i = 1; i < 2; i++) { // needs calibration
        // nothing
    }
}

void short_timer(void) { // human blinkie timescale
    uint32_t on_time  = 2140111222; // it's 2147 something ;)
    for(on_time = 214011; on_time > 0; on_time--) {
        uSec();
    }
}

void wide_timer(void) { // human blinkie timescale
    uint32_t on_time  = 2140111222; // it's 2147 something ;)
    for(on_time = 2140111; on_time > 0; on_time--) {
        uSec();
    }
}

void init_neopixels(void) {
    gpio_init(PORTA, CONFIG_POWER_SENSE_NEOPIX_PIN, 1); // 27
}

/*

bsp/bsp_gpio.h

  6 inline void gpio_init(int port, int pin, int dir) {
  7         PORT->Group[port].DIRSET.reg = ( (dir & 0x01) <<pin);
  8         PORT->Group[port].PINCFG[pin].reg=(uint8_t)(PORT_PINCFG_INEN);
  9 }

*/

void init_act_LED(void) { // PIN_ACTIVITY_LED
    gpio_init(PORTA, PIN_ACTIVITY_LED, 1); // PA17
}

/*

bsp/bsp_gpio.h

 16 inline void gpio_write(int port, int pin, int val) {
 17         if(val) PORT->Group[port].OUTSET.reg = (1ul<<pin);
 18         else PORT->Group[port].OUTCLR.reg = (1ul<<pin);
 19 }

*/

void blink_LED(void) {
 // gpio_write(int port, int pin, int val)
    gpio_write(PORTA, PIN_ACTIVITY_LED, 1); // PA17
    short_timer();
    gpio_write(PORTA, PIN_ACTIVITY_LED, 0); // PA17
    short_timer();
}

uint32_t color = 0;

void to_color(void) {
    // gpio_init(PORTA, CONFIG_POWER_SENSE_NEOPIX_PIN, 1);
    neopix_show_800k(CONFIG_POWER_SENSE_NEOPIX_PIN, (uint8_t *)&color, 4);
    wide_timer();
}

void to_color_st(void) {
    neopix_show_800k(CONFIG_POWER_SENSE_NEOPIX_PIN, (uint8_t *)&color, 4);
    short_timer();
}

void flicker_npx(void) {
    color = 0x090000;    // blue   //
    to_color_st();
    color = 0x000000;    // dark //
    to_color_st();
}

void blinkfast(void) {
    for(int i = 5; i > 0; i--) {
        flicker_npx();
    }
}

void blinkLEDfast(void) {
    for(int i = 15; i > 0; i--) {
        blink_LED();
    }
}

void neo_pixel_demo(void) {
    init_neopixels();

    blinkfast();
    to_color();

    //        BBRRGG
    color = 0x090000;    // blue   //
    to_color();

    color = 0x000000;    // dark //
    to_color();

    wide_timer(); wide_timer(); wide_timer();

    color = 0x001903;    // orange //
    to_color();

    color = 0x090900;    // magenta //
    to_color();
    color = 0x000009;    // green  //
    to_color();
    color = 0x090000;    // blue   //
    to_color();
    color = 0x000900;    // red    //
    to_color();
    color = 0x001903;    // orange //
    to_color();
}

void activity_LED_demo(void) {
    init_act_LED();
    blinkLEDfast();
}

int main(void) {
    board_init(); // Initialize the SAM system
    activity_LED_demo();
    neo_pixel_demo();
    while(1); // ////////////  trap!  ////////////////
}

