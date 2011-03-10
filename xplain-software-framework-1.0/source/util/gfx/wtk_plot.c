/**
 * \file
 *
 * \brief Plot widget implementation
 *
 * Copyright (C) 2009 - 2010 Atmel Corporation. All rights reserved.
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
#include <stdlib.h>
#include <assert.h>
#include <membag.h>
#include <string.h>
#include <gfx/wtk.h>

/**
 * \ingroup gfx_wtk_plot
 * @{
 */

/**
 * \brief Plot control struct.
 * \internal
 *
 * Contains a pointer to the plot's containing window, and non-window
 * information necessary for its operation. Structs of this type are created
 * with \ref wtk_plot_create().
 *
 * \note Structure fields are only internally accessible. Only pointers to
 * these structures are needed externally.
 */
struct wtk_plot {
	//! Container window of plot. 
	struct win_window       *container;
	//! Maximum value of plot.
	uint8_t                 maximum;
	//! Number of datapoints in plot.
	uint8_t                 datapoints;	
	//! Space between datapoints.
	uint8_t                 spacing;	
	//! Error in spacing between datapoints.
	uint8_t                 spacing_error;	
	//! Pointer to ring buffer containing values to plot.
	uint8_t                 *plot_buffer;
	//! Ring buffer start-point displacement
	uint8_t					buffer_start;
	//! Configuration of orientation and behavior.
	uint8_t                 option;
	//! Color for plot.
	gfx_color_t             draw_color;
	//! Color for plot background.
	gfx_color_t             background_color;
};

/**
 * \brief Get pointer to plot window.
 *
 * Returns a reference to the window that should be used when managing the
 * widget, such as destroying, moving or reparenting it.
 *
 * \param plot Pointer to wtk_plot struct to manage.
 *
 * \return Pointer to window to be used for managing the plot.
 */
struct win_window *wtk_plot_as_child(struct wtk_plot *plot)
{
	assert(plot);
	return plot->container;
}




/**
 * \brief Add a value to the end of the plot.
 *
 * Scales the input value to fit the plot dimensions and adds it to the end of 
 * the ring buffer , and issues a redrawing of the plot
 *
 * \param plot Pointer to wtk_plot struct to set new value for.
 * \param value New value for the plot.
 *
 * \return True.
 */
bool wtk_plot_add_value(struct wtk_plot *plot, uint8_t value) 
{
	
	uint8_t length;
	//uint8_t option;
	uint8_t maximum;
	struct win_area const *area;

	assert(plot);
	assert(value <= plot->maximum);
/*  
	if (value != bar->value) {
		bar->value = value;
		option = bar->option;*/
		maximum = plot->maximum;
		
		area = win_get_area(plot->container);

		length = area->size.y;
			
		length -= 2;
		
		
		*(plot->plot_buffer + plot->buffer_start) = 1+wtk_rescale_value((maximum-value), maximum, length);
		
		plot->buffer_start++;
		
		// Increments ring buffer pointer and resets at end
		if(plot->buffer_start >= plot->datapoints)
		{
			plot->buffer_start=0;
		}

		win_redraw(plot->container);

		return true;

}



			/*	/**
				 * \brief Get progress bar value.
				 *
				 * \param bar Pointer to wtk_progress_bar struct to get value from.
				 *
				 * \return Value of progress bar.
				 */
															// TODO: trenger vi noe som denne? (sannsynligvis ikke)
				/*uint8_t wtk_progress_bar_get_value(struct wtk_progress_bar *bar)
				{
					assert(bar);
					return bar->value;
				}
				*/

/**
 * \brief Set new plot colors.
 *
 * This sets new draw and background colors for the plot. 
 *
 * \param plot Pointer to wtk_plot struct to set colors for.
 * \param draw_color Draw color to set for plot.
 * \param background_color Background color to set for plot.
 */
 
void wtk_plot_set_colors(struct wtk_plot *plot,
		gfx_color_t draw_color, gfx_color_t background_color)
{
	assert(plot);
	
	plot->draw_color = draw_color;
	plot->background_color = background_color;
}

/**
 * \brief plot event handler.
 *
 * This is the window event handler for plot widgets. It handles the two
 * relevant event types sent to a plot's container window, i.e., drawing,
 * and destroy events.
 *
 * \param win Window receiving the event.
 * \param type The event type.
 * \param data Custom data, depending on event type.
 *
 * \return True if the event was recognized and accepted.
 */
static bool wtk_plot_handler(struct win_window *win,
		enum win_event_type type, void const *data)
{
	struct win_clip_region const    *clip;
	struct win_area const           *area;
	struct wtk_plot					*plot;
	uint8_t                         option;

	plot = (struct wtk_plot *)win_get_custom_data(win);

	// Window receiving the event should be the widget's containing window.
	assert(win == plot->container);

	switch (type) {
	case WIN_EVENT_DRAW:
		/* For DRAW events, the data parameter points to the clipping
		 * region. The window area parameter is needed because it
		 * contains the size of the widget.
		 */
		clip = (struct win_clip_region const *)data;
		area = win_get_area(win);

		//position = plot->position;
		option = plot->option;

		// Draw a window border.
		gfx_draw_rect(clip->origin.x, clip->origin.y, area->size.x,
				area->size.y, WTK_PROGRESS_BAR_BORDER_COLOR);			
				

		/* Draw plot interior.
		 */
		 
		 gfx_draw_filled_rect(clip->origin.x + 1, 		
					clip->origin.y + 1,
					area->size.x - 2,					
					area->size.y - 2,
					plot->background_color);
		
		uint8_t ring_buffer_offset=plot->buffer_start;
		uint8_t x_error=plot->spacing_error;
		uint8_t x_current=1+plot->spacing;
		uint8_t x_previous=1, y_previous= *(plot->plot_buffer+ring_buffer_offset);
				
		for(uint8_t datapoint=1 ; datapoint < (plot->datapoints); datapoint++) {
			//increment the datapointer around the ring buffer
			ring_buffer_offset++;
			if (ring_buffer_offset>=plot->datapoints) {
				ring_buffer_offset=0;
			}
						
			gfx_draw_line(clip->origin.x+x_previous, 
				clip->origin.y+y_previous,
				clip->origin.x+x_current,
				clip->origin.y + *(plot->plot_buffer+ring_buffer_offset),
				plot->draw_color);
			
			y_previous=*(plot->plot_buffer+ring_buffer_offset);
			x_previous=x_current;
			x_current+=plot->spacing;
			x_error+=plot->spacing_error;
			
			/* Adds together the leftover decimals of spacing error and adds one to the spacing between
			 * two datapoints when it exceeds 1.
			 */
			if (x_error>=100){
				x_current++;
				x_error-=100;
			}
			
		}
		
		/* Always accept DRAW events, as the return value is ignored
		 * anyway for that event type.
		 */
		return true;

	case WIN_EVENT_DESTROY:
		/* Free up all memory allocated by widget.
		 * The window is freed by the window system
		 */
		
		membag_free(plot->plot_buffer);
		membag_free(plot);
		
		return true;

	default:
		return false;
	}
}

/**
 * \brief Create a new plot widget.
 *
 * Allocates the necessary memory and intializes the window and data for
 * plot widgets. If there is not enough memory, the function returns
 * NULL.\n To destroy a plot widget and all its contents, and free its
 * memory, call \ref win_destroy() on the plot's child reference, given
 * by \ref wtk_plot_as_child(), like this:
 * "win_destroy(wtk_plot_as_child(my_plot_ptr));".\par
 *
 * The plotted graph will shift from right to left as new data values are added.
 * Data values will be overwrited in the ring buffer as they shift out of the plot window.
 * The maximum parameter scales the input value to fit the plot dimensions.
 *
 * The datapoints parameter must not exceed the maximum membag size, and never
 * over 255. 
 * 
 *
 * Refer to <gfx/wtk.h> for available configuration options.
 *
 * \param parent Pointer to parent win_window struct.
 * \param area Pointer to win_area struct with position and size of the
 *             plot. Minimum size in both x and y direction is 4 pixels.
 * \param maximum Maximum value of the plot.
 * \param datapoints Number of datapoints of the plot. 
 * \param draw_color Plot drawing color.
 * \param background_color Color for background area.
 * \param option Configuration options for plot.
 *
 * \return Pointer to new plot, if memory allocation was successful.
 */
struct wtk_plot *wtk_plot_create(struct win_window *parent,
		struct win_area const *area, uint8_t maximum, uint8_t datapoints, 
		gfx_color_t draw_color, gfx_color_t background_color,
		uint8_t option)
{
	uint8_t length;
	// Do sanity check on parameters.
	assert(maximum > 0);
	assert(area);
	assert(parent);
	assert(datapoints>1)

	// Attributes scratchpad.
	struct win_attributes attr;
	// Allocate memory for the control data.
	struct wtk_plot *plot =
			membag_alloc(sizeof(struct wtk_plot));
	if (!plot) {
		goto outofmem_plot;
	}
	
	// Allocate memory for the control data.
	plot->plot_buffer =
			membag_alloc(datapoints);
	if (!plot->plot_buffer) {
		goto outofmem_plot_buffer;
	}
	
	

	// Initialize the plot data.
	plot->maximum = maximum;
	plot->datapoints=datapoints;
	//plot->value = value;
	plot->option = option;
	plot->draw_color = draw_color;
	plot->background_color = background_color;
	


	/* Do sanity check of specified window area parameters
	 * according to the orientation of the progress bar.
	 */
	attr.area = *area;
	assert(attr.area.size.x > 4);
	assert(attr.area.size.y > 4);

	
	length = attr.area.size.x;
	length -= 3;
	
	//TO DO! optimeres 
	
	// Calculates the current spacing error.
	plot->spacing = length / (datapoints-1);
	plot->spacing_error = (uint8_t)((((uint16_t)(length-plot->spacing*(datapoints-1)))*100)/((uint16_t)(datapoints-1)));
	

	// Set the progress bar's end position.
	//bar->position = wtk_rescale_value(value, maximum, length);

	/* All drawing is done in wtk_progress_bar_handler() so no background is
	 * needed.
	 */
	attr.background = NULL;
	
	// Set up handling information.
	attr.event_handler = wtk_plot_handler;
	attr.custom = plot;
	
	/* Since the widget has no transparent areas, the parent does not need
	 * to be redrawn.
	 */
	attr.behavior = 0;

	// Create a new window for the progress bar.
	plot->container = win_create(parent, &attr);
	if (!plot->container) {
		goto outofmem_container;
	}

	return plot;

outofmem_container:
	membag_free(plot->plot_buffer);

outofmem_plot_buffer:	
	membag_free(plot);

outofmem_plot:
	return NULL;
}

//! @}
