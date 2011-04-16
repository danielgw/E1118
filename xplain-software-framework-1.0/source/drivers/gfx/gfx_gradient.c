/**
* \file
*
* \brief Gradient drawing graphics routines
*
* Copyright (C) 2009-2010 Atmel Corporation. All rights reserved.
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

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <gfx/gfx.h>


#ifdef CONFIG_GRADIENT

/**
 * \brief Draw a gradient
 *
 * Draw a bitmap to the screen on the given display coordinates.
 *
 * \param gradient  Pointer to gradient.
 * \param map_x     X coordinate inside gradient.
 * \param map_y     Y coordinate inside gradient.
 * \param x         X coordinate on screen.
 * \param y         Y coordinate on screen.
 * \param width     Width of gradient to draw.
 * \param height    Height of gradient to draw.
 */

 void gfx_gradient_draw(struct gfx_gradient *gradient, 
		gfx_coord_t map_x, gfx_coord_t map_y,
		gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width,gfx_coord_t height){

	uint16_t color_r= (((uint16_t)(gradient->start_r)) << 8);
	uint16_t color_g= (((uint16_t)(gradient->start_g)) << 8);
	uint16_t color_b= (((uint16_t)(gradient->start_b)) << 8);

	uint16_t delta_r= gradient->delta_r;
	uint16_t delta_g= gradient->delta_g;
	uint16_t delta_b= gradient->delta_b;

	gfx_coord_t x2 = x + width;
	gfx_coord_t y2 = y + width;

	if ((gradient->option)&(GFX_GRADIENT_INVERT)){
		color_r += (delta_r * (gradient->length - 1));
		color_g += (delta_g * (gradient->length - 1));
		color_b += (delta_b * (gradient->length - 1));

		delta_r = -delta_r;
		delta_g = -delta_g;
		delta_b = -delta_b;
	}

	if (((gradient->option)&
			(GFX_GRADIENT_MIRROR|GFX_GRADIENT_HORIZONTAL)) == 
			(GFX_GRADIENT_MIRROR|GFX_GRADIENT_HORIZONTAL)){
			
		gfx_coord_t x3 = (gradient->length / 2);
		x -= map_x;
		x2 = x + gradient->length;
		gfx_coord_t x4 = gradient->length - (width + map_x); 
		
		for(gfx_coord_t index_x = 0; index_x <= x3; index_x++){
			if (index_x >= map_x){
				gfx_draw_vertical_line(x + index_x, y, height,
						GFX_COLOR(
						(uint8_t)(color_r >> 8),
						(uint8_t)(color_g >> 8),
						(uint8_t)(color_b >> 8)));
			}
			if (index_x>=x4){
				gfx_draw_vertical_line(x2 - index_x, y, height,
						GFX_COLOR(
						(uint8_t)(color_r >> 8),
						(uint8_t)(color_g >> 8),
						(uint8_t)(color_b >> 8)));
			}
			
			color_r += delta_r;
			color_g += delta_g;
			color_b += delta_b;
		}

	} else 	if (((gradient->option)&
			(GFX_GRADIENT_MIRROR|GFX_GRADIENT_VERTICAL)) == 
			(GFX_GRADIENT_MIRROR|GFX_GRADIENT_VERTICAL)){

		gfx_coord_t y3 = (gradient->length / 2);
		y -= map_y;
		y2 = y + gradient->length;
		gfx_coord_t y4 = gradient->length - (height + map_y); 
		
		for(gfx_coord_t index_y = 0 ; index_y <= y3; index_y++){

			if (index_y >= map_y){
				gfx_draw_horizontal_line(x, y + index_y, width,
						GFX_COLOR(
						(uint8_t)(color_r >> 8),
						(uint8_t)(color_g >> 8),
						(uint8_t)(color_b >> 8)));
			}
			if (index_y >= y4){
				gfx_draw_horizontal_line(x, y2 - index_y, width,
						GFX_COLOR(
						(uint8_t)(color_r >> 8),
						(uint8_t)(color_g >> 8),
						(uint8_t)(color_b >> 8)));
			}
			
			color_r += delta_r;
			color_g += delta_g;
			color_b += delta_b;
		}

	} else {

		if ((gradient->option) & (GFX_GRADIENT_HORIZONTAL)){
			if (map_x  > 0){
				color_r += (delta_r * map_x);
				color_g += (delta_g * map_x);
				color_b += (delta_b * map_x);
			}

			for(gfx_coord_t index_x = x; index_x <= x2 ; index_x++){

				gfx_draw_vertical_line(index_x, y, height,
						GFX_COLOR(
						(uint8_t)(color_r >> 8),
						(uint8_t)(color_g >> 8),
						(uint8_t)(color_b >> 8)));
				color_r += delta_r;
				color_g += delta_g;
				color_b += delta_b;
			}
		} else {
			
			if (map_y  > 0){
				color_r += (delta_r * map_y);
				color_g += (delta_g * map_y);
				color_b += (delta_b * map_y);
			}
			for(gfx_coord_t index_y = y; index_y <= y2 ; index_y++){

				gfx_draw_horizontal_line(x, index_y, width,
						GFX_COLOR(
						(uint8_t)(color_r >> 8),
						(uint8_t)(color_g >> 8),
						(uint8_t)(color_b >> 8)));
				color_r += delta_r;
				color_g += delta_g;
				color_b += delta_b;
			}
		}
	}
}
#endif

