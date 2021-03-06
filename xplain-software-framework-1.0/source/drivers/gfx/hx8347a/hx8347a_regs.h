/**
 * \file
 *
 * \brief HX8347A Display Controller register definitions
 *
 * Copyright (C) 2009 Atmel Corporation. All rights reserved.
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 * Atmel AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */
#ifndef DRIVERS_GFX_HX8347A_HX8347A_REGS_H_INCLUDED
#define DRIVERS_GFX_HX8347A_HX8347A_REGS_H_INCLUDED

/* --- SPI communication start byte bit fields --- */

#define HX8347A_START_ID  0x70
#define HX8347A_START_BS0 0x04
#define HX8347A_START_RS  0x02
#define HX8347A_START_RW  0x01

#define HX8347A_START_WRITEIDX (HX8347A_START_ID | HX8347A_START_BS0)
#define HX8347A_START_WRITEREG (HX8347A_START_ID | HX8347A_START_BS0 | HX8347A_START_RS)
#define HX8347A_START_READREG (HX8347A_START_ID | HX8347A_START_BS0 | HX8347A_START_RS | HX8347A_START_RW)


/* --- HIMAX controller register addresses and bit values --- */

#define HX8347A_DISPMODECTRL 0x01
#define HX8347A_INVON 2

#define HX8347A_COLSTARTHIGH 0x02
#define HX8347A_COLSTARTLOW  0x03
#define HX8347A_COLENDHIGH   0x04
#define HX8347A_COLENDLOW    0x05
#define HX8347A_ROWSTARTHIGH 0x06
#define HX8347A_ROWSTARTLOW  0x07
#define HX8347A_ROWENDHIGH   0x08
#define HX8347A_ROWENDLOW    0x09

#define HX8347A_MEMACCESSCTRL 0x16
#define HX8347A_MY 7
#define HX8347A_MX 6
#define HX8347A_MV 5
#define HX8347A_BGR 3

#define HX8347A_OSCCTRL1 0x19
#define HX8347A_OSC_EN 0 // Default 0
#define HX8347A_OSCCTRL2 0x1A
#define HX8347A_OSCCTRL3 0x93

#define HX8347A_POWERCTRL1 0x1B
#define HX8347A_GASENB   7 // Default 0
#define HX8347A_PON      4 // Default 0
#define HX8347A_DK       3 // Default 1
#define HX8347A_XDK      2 // Default 0
#define HX8347A_VTFT_TRI 1 // Default 0
#define HX8347A_STB      0 // Default 1

#define HX8347A_POWERCTRL2 0x1C
#define HX8347A_AP2 2 // Default 0
#define HX8347A_AP1 1 // Default 0
#define HX8347A_AP0 0 // Default 0
#define HX8347A_POWERCTRL3 0x1D
#define HX8347A_POWERCTRL4 0x1E
#define HX8347A_POWERCTRL5 0x1F
#define HX8347A_POWERCTRL6 0x20

#define HX8347A_SRAMWRITE 0x22
#define HX8347A_CYCLECTRL1_X 0x23
#define HX8347A_CYCLECTRL2_X 0x24
#define HX8347A_CYCLECTRL3_X 0x25

#define HX8347A_DISPCTRL1 0x26
#define HX8347A_PT1 7 // Default 0
#define HX8347A_PT0 6 // Default 0
#define HX8347A_GON 5 // Default 1
#define HX8347A_DTE 4 // Default 0
#define HX8347A_D1  3 // Default 0
#define HX8347A_D0  2 // Default 0
#define HX8347A_DISPCTRL2 0x27
#define HX8347A_DISPCTRL3 0x28
#define HX8347A_DISPCTRL4 0x29
#define HX8347A_DISPCTRL5 0x2A
#define HX8347A_DISPCTRL6 0x2C
#define HX8347A_DISPCTRL7 0x2D
#define HX8347A_DISPCTRL9 0x35
#define HX8347A_DISPCTRL10 0x36

#define HX8347A_CYCLECTRL1 0x3A
#define HX8347A_CYCLECTRL2 0x3B
#define HX8347A_CYCLECTRL3 0x3C
#define HX8347A_CYCLECTRL4 0x3D
#define HX8347A_CYCLECTRL5 0x3E
#define HX8347A_CYCLECTRL6 0x40
#define HX8347A_CYCLECTRL7 0x41

#define HX8347A_VCOMCTRL1 0x43
#define HX8347A_VCOMG 7 // Default 0
#define HX8347A_VCOMCTRL2 0x44
#define HX8347A_VCOMCTRL3 0x45

#define HX8347A_GAMMACTRL1  0x46
#define HX8347A_GAMMACTRL2  0x47
#define HX8347A_GAMMACTRL3  0x48
#define HX8347A_GAMMACTRL4  0x49
#define HX8347A_GAMMACTRL5  0x4A
#define HX8347A_GAMMACTRL6  0x4B
#define HX8347A_GAMMACTRL7  0x4C
#define HX8347A_GAMMACTRL8  0x4D
#define HX8347A_GAMMACTRL9  0x4E
#define HX8347A_GAMMACTRL10 0x4F
#define HX8347A_GAMMACTRL11 0x50
#define HX8347A_GAMMACTRL12 0x51

#define HX8347A_INTERNAL28 0x70
#define HX8347A_TEON 3

#define HX8347A_SAP 0x90
#define HX8347A_DISPCTRL8 0x90

//! Bitmask used by gfx_set_orientation to flip X direction.
#define GFX_HX_FLIP_X (1 << HX8347A_MX)
//! Bitmask used by gfx_set_orientation to flip Y direction.
#define GFX_HX_FLIP_Y (1 << HX8347A_MY)
//! Bitmask used by gfx_set_orientation to switch X and Y corrdinates.
#define GFX_HX_SWITCH_XY (1 << HX8347A_MV)


#endif /* DRIVERS_GFX_HX8347A_HX8347A_REGS_H_INCLUDED */
