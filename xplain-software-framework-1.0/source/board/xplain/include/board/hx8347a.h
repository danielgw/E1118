/**
 * \file
 *
 * \brief HX8347A board-specific definitions
 *
 * Copyright (C) 2010 Atmel Corporation. All rights reserved.
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
#ifndef BOARD_HX8347A_H_INCLUDED
#define BOARD_HX8347A_H_INCLUDED

#define GFX_DEFAULT_ORIENTATION (GFX_FLIP_Y | GFX_SWITCH_XY)

#define GFX_USART_MODULE        USARTD1
#define GFX_USART_TRIGGER       DMA_CH_TRIGSRC_USARTD1_DRE_gc

#define GFX_CS_PORT             PORTD
#define GFX_CS_PINMASK          PIN4_bm

#define GFX_USART_PORT          PORTD
#define GFX_XCK_PINMASK         PIN5_bm
#define GFX_RXD_PINMASK         PIN6_bm
#define GFX_TXD_PINMASK         PIN7_bm

#define GFX_BACKLIGHT_PIN       CREATE_GPIO_PIN(PORTD, 0)
#define GFX_RESET_PIN           CREATE_GPIO_PIN(PORTD, 1)
#define GFX_TE_PIN              CREATE_GPIO_PIN(PORTD, 2)

#endif /* BOARD_HX8347A_H_INCLUDED */
