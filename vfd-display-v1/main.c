/*
 * vfd-display-v1.c
 *
 * Created: 30.04.2016 10.08.54
 * Author : magnehh
 */ 

// #define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "time.h"
#include "vfd.h"

void initTimer(void);


int main(void){
	
	initTimer();
	
	_delay_ms(500);

	Vfd_ctrl vfdisplay;
	
	vfdisplay.vfd_wr_port = &PORTC;
	vfdisplay.vfd_wr_ddr = &DDRC;
	vfdisplay.vfd_wr_pin_mask = _BV(PC0);
	vfdisplay.vfd_a0_port = &PORTC;
	vfdisplay.vfd_a0_ddr = &DDRC;
	vfdisplay.vfd_a0_pin_mask = _BV(PC1);
	vfdisplay.vfd_data_port = &PORTD;
	vfdisplay.vfd_data_ddr = &DDRD;
	
	vfd_init(vfdisplay);
	vfd_putc(vfdisplay,VFD_CMD_DC5);
	
	char currentTime[] = "13:37";
	char sunriseTime[] = "14:63";
	char sunsetTime[] = "42:42";
	
	sei();
	
	
	
	struct tm rtc_time;
	read_rtc(&rtc_time);
	rtc_time.tm_isdst = 0;

	set_system_time(mktime(&rtc_time));
	
	
    while(1){
		
		vfd_putcmd(vfdisplay,0x00);			// Set cursor position to upper leftmost position
		
		vfd_puts(vfdisplay,"Time: ");
		vfd_puts(vfdisplay,(char*)currentTime);
		vfd_puts(vfdisplay," Sunrise: ");
		vfd_puts(vfdisplay,sunriseTime);
		vfd_puts(vfdisplay," Sunset: ");
		vfd_puts(vfdisplay,sunsetTime);
		
		vfd_putcmd(vfdisplay,0x28);			// Set cursor position to lower leftmost position
		
		vfd_putc(vfdisplay,'[');
		
		for (uint8_t i = 0; i < 28; i++){
			vfd_putc(vfdisplay,'=');
		}
		
		vfd_putc(vfdisplay,'>');
		
		vfd_putcmd(vfdisplay,0x4F);			// Set cursor position to lower rightmost position
		vfd_putc(vfdisplay,']');
		
		_delay_ms(1000);					// Delay to avoid flicker
		
	}
	
}

void initTimer(void){
	TCCR2A = 0x00;
	TCCR2B = _BV(CS22) | _BV(CS20);
	TCNT2 = 0x00;
	TIMSK2 = _BV(TOIE2);
	TIFR2 = _BV(OCF2B) | _BV(OCF2A) | _BV(TOV2);
	ASSR = _BV(AS2);
}

ISR(TIMER2_OVF_vect){
	
}