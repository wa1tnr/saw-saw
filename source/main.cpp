// Tue 17 Jul 02:58:18 UTC 2018
// main.cpp

/*
 * Created: 7/17/2017 3:26:42 PM
 * Author : deanm
 */ 

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

void neo_pixel_demo(void) {
    init_neopixels();
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
	
	QF::init();
	QF::poolInit(evtPoolSmall, sizeof(evtPoolSmall), EVT_SIZE_SMALL);
	QF::poolInit(evtPoolMedium, sizeof(evtPoolMedium), EVT_SIZE_MEDIUM);
	QF::poolInit(evtPoolLarge, sizeof(evtPoolLarge), EVT_SIZE_LARGE);
	QP::QF::psInit(subscrSto, Q_DIM(subscrSto)); // init publish-subscribe
	
	BspInit();

	//Start active objects.
	sys.Start(PRIO_SYSTEM);
	del.Start(PRIO_DELEGATE);
	
#if CONFIG_I2C_SLAVE
	i2c.Start(PRIO_I2C_SLAVE);
#endif
	
#if CONFIG_ADC
	adc.Start(PRIO_ADC);
#endif

#if CONFIG_DAC
	dac.Start(PRIO_DAC);
#endif

#if CONFIG_TIMER
	tmr.Start(PRIO_TIMER);
#endif

#if CONFIG_TOUCH
    touch.Start(PRIO_TOUCH);
#endif

#if CONFIG_INTERRUPT
	interrupt.Start(PRIO_INTERRUPT);
#endif

#if CONFIG_SERCOM0
	sercom0.Start(PRIO_SERCOM);
#endif

#if CONFIG_SERCOM1
	sercom1.Start(PRIO_SERCOM);
#endif

#if CONFIG_SERCOM2
	sercom2.Start(PRIO_SERCOM);
#endif

#if CONFIG_SERCOM5
	sercom5.Start(PRIO_SERCOM);
#endif

#if CONFIG_DAP
	dap.Start(PRIO_DAP);
#endif

// ---- last one wins:
#undef  NEVER_DEFINED_COMMENTED // disable NEOPIXEL handler
#define NEVER_DEFINED_COMMENTED // enable  NEOPIXEL handler
// ---- :last one wins

#ifdef NEVER_DEFINED_COMMENTED
#if CONFIG_NEOPIXEL
	neopixel.Start(PRIO_NEOPIXEL);
#endif
#endif // #ifdef NEVER_DEFINED_COMMENTED
	
	//publish a start request
	Evt *evt = new SystemStartReq(0);
	QF::PUBLISH(evt, dummy);
	
	QP::QF::run();
}

*/
