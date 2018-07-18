// Wed 18 Jul 22:16:10 UTC 2018
// main.cpp

// previous timestamp:
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

int main(void)
{
    /* Initialize the SAM system */
    board_init();
    neo_pixel_demo();
    while(1); // ////////////  trap!  ////////////////
}

/*      // big comment-out block AA: 
*/
