/*************************************************************************
Title:    vfd library
Author:   Magne Haneberg <magnehh |at| stud |.| ntnu |.| no>
Software: AVR-GCC 4.x
Hardware: AVR8 
License:  GNU General Public License 
          
DESCRIPTION:
    Library to communicate with Noritake Itron vacuum fluorescent display.
                    
LICENSE:
    Copyright (C) 2016 Magne Haneberg, GNU General Public License Version 3

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
                        
*************************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "vfd.h"


void vfd_init(Vfd_ctrl vfd_ctrl){
	
	*vfd_ctrl.vfd_wr_port |= vfd_ctrl.vfd_wr_pin_mask;	// High
	*vfd_ctrl.vfd_wr_ddr |= vfd_ctrl.vfd_wr_pin_mask;	// Output
	
	*vfd_ctrl.vfd_a0_port |= vfd_ctrl.vfd_a0_pin_mask;	// High
	*vfd_ctrl.vfd_a0_ddr |= vfd_ctrl.vfd_a0_pin_mask;	// Output
	
	*vfd_ctrl.vfd_data_port = 0x00;
	*vfd_ctrl.vfd_data_ddr = 0xFF;
	
	vfd_reset(vfd_ctrl);
	
}


void vfd_putc(Vfd_ctrl vfd_ctrl,char data){

	*vfd_ctrl.vfd_data_port = data;		// Character or command
	
	*vfd_ctrl.vfd_a0_port &= ~(vfd_ctrl.vfd_a0_pin_mask);	// Set low
	
	*vfd_ctrl.vfd_wr_port &= ~(vfd_ctrl.vfd_wr_pin_mask);	// Set low
	_delay_us(1);											// Delay according to datasheet
	*vfd_ctrl.vfd_wr_port |= vfd_ctrl.vfd_wr_pin_mask;		// Set high
	
	_delay_us(VFD_EXEC_DELAY);
	
}


void vfd_putcmd(Vfd_ctrl vfd_ctrl,char data){
	
	*vfd_ctrl.vfd_data_port = data;		// Character or command
	
	*vfd_ctrl.vfd_a0_port |= vfd_ctrl.vfd_a0_pin_mask;	// Set high
	
	*vfd_ctrl.vfd_wr_port &= ~(vfd_ctrl.vfd_wr_pin_mask);	// Set low
	_delay_us(1);											// Delay according to datasheet
	*vfd_ctrl.vfd_wr_port |= vfd_ctrl.vfd_wr_pin_mask;		// Set high
		
	_delay_us(VFD_EXEC_DELAY);
	
}


void vfd_puts(Vfd_ctrl vfd_ctrl, char *string){
	
	for (uint8_t i = 0; i < strlen(string); i++){
		
		vfd_putc(vfd_ctrl, string[i]);
		
	}
	
}


// void vfd_customFont(Vfd_ctrl vfd_ctrl);


void vfd_reset(Vfd_ctrl vfd_ctrl){
	vfd_putcmd(vfd_ctrl, 0x50);
	_delay_ms(100);
}