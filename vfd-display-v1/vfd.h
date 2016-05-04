/*************************************************************************
Title:    vfd library
Author:   Magne Haneberg <magnehh |at| stud |.| ntnu |.| no>
Software: AVR-GCC 4.x
Hardware: AVR8 
License:  GNU General Public License 
          
DESCRIPTION:
    Library to communicate with Noritake Itron vacuum fluorescent display.
	/RD line on VFD module should be tied to Vcc. This library never reads.
                    
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

#ifndef VFD_H
#define VFD_H

/** 
 *  @file
 *  @code #include <vfd.h> @endcode
 * 
 *  @brief vfd library
 *
 *  @author Magne Haneberg <magnehh |at| stud |.| ntnu |.| no>
 *  @copyright (C) 2016 Magne Haneberg, GNU General Public License Version 3
 */

#define VFD_CMD_BS 0x08
#define VFD_CMD_HT 0x09
#define VFD_CMD_LF 0x0A
#define VFD_CMD_CR 0x0D
#define VFD_CMD_DC1 0x11
#define VFD_CMD_DC2	0x12
#define VFD_CMD_DC3	0x13
#define VFD_CMD_DC4	0x14
#define VFD_CMD_DC5	0x15
#define VFD_CMD_DC6	0x16
#define VFD_CMD_SUB	0x1A
#define VFD_CMD_ESC	0x1B
#define VFD_CMD_FS	0x1C
#define VFD_CMD_GS	0x1D
#define VFD_CMD_RS	0x1E
#define VFD_CMD_US	0x1F

#define VFD_EXEC_DELAY 200


struct vfd_ctrl {
	volatile uint8_t *vfd_wr_port;
	volatile uint8_t *vfd_wr_ddr;
	volatile uint8_t vfd_wr_pin_mask;
	volatile uint8_t *vfd_a0_port;
	volatile uint8_t *vfd_a0_ddr;
	volatile uint8_t vfd_a0_pin_mask;
	volatile uint8_t *vfd_data_port;
	volatile uint8_t *vfd_data_ddr;
};

typedef struct vfd_ctrl Vfd_ctrl;


/** @brief  Initializing function
 *  @param  spi_cs_port The port where chip select lines are located
 *  @param  spi_cs_ddr Data direction register of chip select lines
 *	@param	spi_cs_pin_mask Mask of pins to be used as chip select lines
 *	@return	none
 */
void vfd_init(Vfd_ctrl);


/** @brief  Function to read the entire string of four bytes presented by the MAX31855
 *  @param  spi_cs_port The port where chip select lines are located
 *	@param	spi_cs_pin Pin connected to desired chip select line
 *	@return 32bit word received from MAX31855
 */
void vfd_putc(Vfd_ctrl,char);


/** @brief  Function to read the entire string of four bytes presented by the MAX31855
 *  @param  spi_cs_port The port where chip select lines are located
 *	@param	spi_cs_pin Pin connected to desired chip select line
 *	@return 32bit word received from MAX31855
 */
void vfd_putcmd(Vfd_ctrl,char);


/** @brief  Function to read the entire string of four bytes presented by the MAX31855
 *  @param  spi_cs_port The port where chip select lines are located
 *	@param	spi_cs_pin Pin connected to desired chip select line
 *	@return 32bit word received from MAX31855
 */
void vfd_puts(Vfd_ctrl,char*);


// /** @brief  Function to read the entire string of four bytes presented by the MAX31855
//  *  @param  spi_cs_port The port where chip select lines are located
//  *	@param	spi_cs_pin Pin connected to desired chip select line
//  *	@return 32bit word received from MAX31855
//  */
// void vfd_customFont(Vfd_ctrl);


/** @brief  Function to read the entire string of four bytes presented by the MAX31855
 *  @param  spi_cs_port The port where chip select lines are located
 *	@param	spi_cs_pin Pin connected to desired chip select line
 *	@return 32bit word received from MAX31855
 */
void vfd_reset(Vfd_ctrl);


#endif /* VFD_H */