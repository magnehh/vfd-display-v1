/*
 * vfd-display-v1.c
 *
 * Created: 30.04.2016 10.08.54
 * Author : magnehh
 */ 

// #define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "vfd.h"


int main(void){
	
	_delay_ms(250);

	Vfd_ctrl vfdisplay;
	
	vfdisplay.vfd_wr_port = &PORTC;
	vfdisplay.vfd_wr_ddr = &DDRC;
	vfdisplay.vfd_wr_pin_mask = _BV(PC0);
	vfdisplay.vfd_a0_port = &PORTC;
	vfdisplay.vfd_a0_ddr = &DDRC;
	vfdisplay.vfd_a0_pin_mask = _BV(PC1);
	vfdisplay.vfd_cs_port = &PORTC;
	vfdisplay.vfd_cs_ddr = &DDRC;
	vfdisplay.vfd_cs_pin_mask = _BV(PC3);
	vfdisplay.vfd_busy_port = &PORTC;
	vfdisplay.vfd_busy_ddr = &DDRC;
	vfdisplay.vfd_busy_pin = &PINC;
	vfdisplay.vfd_busy_pin_mask = _BV(PC2);
	vfdisplay.vfd_reset_port = &PORTC;
	vfdisplay.vfd_reset_ddr = &DDRC;
	vfdisplay.vfd_reset_pin_mask = _BV(PC4);
	vfdisplay.vfd_data_port = &PORTD;
	vfdisplay.vfd_data_ddr = &DDRD;
	
	vfd_init(vfdisplay);
	vfd_putc(vfdisplay,VFD_CMD_DC5);
	
	char currentTime[] = "13:37";
	char sunriseTime[] = "14:63";
	char sunsetTime[] = "42:42";

    while(1){
		
		vfd_putcmd(vfdisplay,0x00);
		
		vfd_puts(vfdisplay,"Time: ");
		vfd_puts(vfdisplay,currentTime);
		vfd_puts(vfdisplay," Sunrise: ");
		vfd_puts(vfdisplay,sunriseTime);
		vfd_puts(vfdisplay," Sunset: ");
		vfd_puts(vfdisplay,sunsetTime);
		
		vfd_putcmd(vfdisplay,0x28);
		
		for (uint8_t i = 0; i < 40; i++){
			vfd_putc(vfdisplay,0x7F);
		}
		

		
		_delay_ms(250);
		
	}
	
}

