/**
 * \file
 *
 * \brief Dialogue box widget implementation
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
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <membag.h>
#include <string.h>
#include <gfx/wtk.h>
#include <mainloop.h>




//! Drawn dialogue box positions and size

#define DIALOGUE_FRAME_POS_X        40

#define DIALOGUE_FRAME_POS_Y        50

#define DIALOGUE_FRAME_SIZE_X      240

#define DIALOGUE_FRAME_SIZE_Y      130

#define BUTTON_SIZE_X               90

#define BUTTON_SIZE_Y               40

#define BUTTON_POS_Y                60

#define BUTTON_SPACING              20

#define DIALOGUE_BOX_BACKGROUND     GFX_COLOR(100, 100, 100)

//! Label position on top of display
#define CAPTION_POS_X               DIALOGUE_FRAME_SIZE_X / 2
//! Label position on top of display
#define CAPTION_POS_Y               10

#define SECOND_CAPTION_POS_X           CAPTION_POS_X

#define SECOND_CAPTION_POS_Y           40


/**
 * \brief Event command ID for the component widgets.
 *
 * \note The command IDs cannot be 0, since this value is reserved for no
 * command event callback for certain widgets.
 */
enum app_widget_ids {
	//! Event command ID for the OK button.
	BUTTON_OK_ID = 1,
	
	BUTTON_CANCEL_ID = 2,
};


/**
 * \brief Dialogue box control struct
 *
 * This is the dialogue box control struct. It contains references to the window
 * composing the dialogue box, as well as non-window information required.
 *
 * \internal
 * \note Structure fields are only internally accessible, only pointers to
 *       structure is needed externally.
 */
struct wtk_dialogue_box {
	//! Copy of caption string.
	char                    *caption;
	
	char                    *second_caption;
	
	//! Custom command data, used when "clicked".
	win_command_t           command_data;
};


/**
 * \brief Dialogue box command events handler
 *
 * This function handles the command events generated by the widgets.
 *
 * \sa wtk_basic_frame_command_handler_t 			// denne gj�r ett eller annet DOX-relatert
 */								//noen b�r sikkert finne ut hva
static bool dialogue_box_command_handler(struct wtk_basic_frame *frame,
		win_command_t command_data)
{
	char command = (char)(uintptr_t)command_data;

		struct wtk_dialogue_box *dialogue_box;
		dialogue_box = (struct wtk_dialogue_box*)
				wtk_basic_frame_get_custom_data(frame);


		struct win_window *dialogue_win = 
				win_get_parent(wtk_basic_frame_as_child(frame));

		struct win_window *dialogue_parent = 
				win_get_parent(dialogue_win);
	
		switch (command) {
	

	
	case BUTTON_OK_ID:

		win_grab_pointer(NULL);

		struct win_command_event send_command;

		/* Send the supplied command event to the frame from which the 
		 * dialogue box originated
		 */

		send_command.sender = dialogue_parent;
		send_command.recipient = dialogue_parent;
		send_command.data = dialogue_box->command_data;

		win_queue_command_event(&send_command);

		//free memory of button, frame, and box.
		win_destroy(dialogue_win);

		break;
		
	case BUTTON_CANCEL_ID:

		win_grab_pointer(NULL);

		//free memory of button, frame, and box.
		win_destroy(dialogue_win);

		break;
	}

	return false;
}

/**
 * \brief Dialogue box frame draw event handler
 *
 * This function will draw the frame and background of the dialogue box.
 *
 * \sa wtk_basic_frame_draw_handler_t							//DOXYGEN! 
 */
static void dialogue_box_draw_handler(struct win_window *win,
		struct win_clip_region const *clip)
{							//TODO: make it pretty! (kanter? ettellerannetiaffal)

	//TODO: FIKS DISSE!					NEIN!					UFFOGHUFF
	gfx_draw_rect(0, 0,
		gfx_get_width()/2,
		gfx_get_height()/2, GFX_COLOR(200, 200, 200));
	
}


/**
 * \brief Dialogue box event handler
 *
 * This function is the window event handler for dialogue box widgets.
 * It handles all events sent to the windows composing the widget.
 *
 * \param win  Window receiving the event.
 * \param type The event type.
 * \param data Custom data, depending on event type.
 *
 * \return True if the event was recognized and accepted.
 */
static bool wtk_dialogue_box_event_handler(struct win_window *win,
		enum win_event_type type, const void *data)
{
	// Custom data for windows of a widget points back to the widget itself.
	struct wtk_dialogue_box *dialogue_box;

	dialogue_box = win_get_custom_data(win);

	switch (type) {
	case WIN_EVENT_DRAW:
		/* For DRAW events, the data parameter points to the
		 * clipping region.
		 */

		/* Always accept DRAW events, as the return value is
		 * ignored anyway for that event type.
		 */
		return true;

	case WIN_EVENT_POINTER:
		/* Accept all POINTER events so that it does not
		 * propagate up the window tree to our parent in case
		 * we did not click anything useful inside the frame.
		 */
		return true;

	case WIN_EVENT_DESTROY:
		/* When the frame window is destroyed, also destroy
		 * the rest of the non-window frame allocations.
		 */
		membag_free(dialogue_box);
		//}

		/* Always accept DESTROY events, as the return value is
		 * ignored anyway for that event type.
		 */
		return true;

	default:
		// Reject unknown event types.
		return false;

	}
}



/**
 * \brief Create dialogue box widget
 *
 * This function creates a new dialogue box widget. It allocates required memory
 * and intializes necessary windows to create the widget. If there is not enough
 * memory, the function returns NULL.
 *
 * To destroy the widget and all its contents, and free its memory, call
 * win_destroy() on the basic frame's child reference, given by
 * wtk_basic_frame_as_child(), like this:
 * "win_destroy(wtk_basic_frame_as_child(my_frame_ptr));".
 *
 * \param parent         Parent window.
 * \param area           Area of the internal contents.
 * \param background     Pointer to background bitmap for frame. NULL for
 *                       transparent background. When background is transparent
 *                       the parent window will automatically be redrawn
 *                       when the basic frame is drawn.
 * \param draw_handler   Draw event handler. NULL for no handler.
 * \param frame_handler  Command event handler. NULL for no handler.
 * \param custom_data    Optional custom data link for application's command
 *                       events.
 *
 * \return Pointer to basic frame, or NULL if failed.
 */
struct win_window *wtk_dialogue_box_create(struct win_window *parent,
		char *caption, char *second_caption, win_command_t command_data)
{
	struct win_attributes       attr;
	struct gfx_bitmap           dialogue_background;
	struct win_window           *dialogue_window;
	struct wtk_basic_frame      *dialogue_frame;
	struct wtk_dialogue_box     *dialogue_struct;
	struct wtk_button           *button_ok, *button_cancel;
	struct wtk_label        	*label;
	struct wtk_label            *second_label;
	struct win_area             area;

	assert(area);
	assert(parent);

	/* set up the container window, making it as large as the screen to 
	 * absorb pointer events.
	 */


	// Allocate memory for dialogue box data.
	dialogue_struct = membag_alloc(sizeof(struct wtk_dialogue_box));
	if (!dialogue_struct) {
		goto outofmem_dialogue_struct;
	}

	area.pos.x = 0;
	area.pos.y = 0;
	area.size.x = gfx_get_width();
	area.size.y = gfx_get_height();

	attr.area = area;
	attr.event_handler = wtk_dialogue_box_event_handler;
	attr.custom = dialogue_struct;
	attr.background = NULL;
	attr.behavior = 0;

	dialogue_window = win_create(parent, &attr);
	if (!dialogue_window) {
		goto outofmem_win;
	}


	dialogue_struct->command_data = command_data;
	dialogue_struct->caption = caption;
	dialogue_struct->second_caption = second_caption;

	area.pos.x = DIALOGUE_FRAME_POS_X;
	area.pos.y = DIALOGUE_FRAME_POS_Y;
	area.size.x = DIALOGUE_FRAME_SIZE_X;
	area.size.y = DIALOGUE_FRAME_SIZE_Y;

	dialogue_background.type = BITMAP_SOLID;
	dialogue_background.data.color = DIALOGUE_BOX_BACKGROUND;
	
	dialogue_frame = wtk_basic_frame_create(dialogue_window, &area,
			&dialogue_background,dialogue_box_draw_handler,
			dialogue_box_command_handler, dialogue_struct);
	if (!dialogue_frame) {
		goto error_widget;
	}

	
	
	area.pos.x = CAPTION_POS_X;
	area.pos.y = CAPTION_POS_Y;
	
	// Find an optimal size for the widget.
	wtk_label_size_hint(&area.size, caption);

	/*
	 * Create the label and check the return value if an error occured
	 * while creating the label.
	 */
	label = wtk_label_create(wtk_basic_frame_as_child(dialogue_frame), &area, dialogue_struct->caption, false);
	if (!label) {
		goto error_widget;
	}
	
	
	area.pos.x = SECOND_CAPTION_POS_X;
	area.pos.y = SECOND_CAPTION_POS_Y;
	
	// Find an optimal size for the widget.
	wtk_label_size_hint(&area.size, second_caption);

	/*
	 * Create the label and check the return value if an error occured
	 * while creating the label.
	 */
	second_label = wtk_label_create(wtk_basic_frame_as_child(dialogue_frame), &area, dialogue_struct->second_caption, false);
	if (!label) {
		goto error_widget;
	}

	
	// Ok button position and size
	area.pos.x = DIALOGUE_FRAME_SIZE_X / 2 - BUTTON_SIZE_X - BUTTON_SPACING / 2;
	area.pos.y = BUTTON_POS_Y;
	area.size.x = BUTTON_SIZE_X;
	area.size.y = BUTTON_SIZE_Y;

	button_ok = wtk_button_create(wtk_basic_frame_as_child(dialogue_frame), 
			&area, "OK", (win_command_t)BUTTON_OK_ID);
	if (!button_ok) {
		goto error_widget;
	}

	// Cancel button position and size
	area.pos.x = DIALOGUE_FRAME_SIZE_X / 2 + BUTTON_SPACING / 2;
	area.pos.y = BUTTON_POS_Y;
	
	button_cancel = wtk_button_create(wtk_basic_frame_as_child(dialogue_frame), 
			&area, "Cancel", (win_command_t)BUTTON_CANCEL_ID);
	if (!button_ok) {
		goto error_widget;
	}


	win_show(wtk_basic_frame_as_child(dialogue_frame)); 

	// Draw the label by showing the label widget's window.
	win_show(wtk_label_as_child(label));
	win_show(wtk_label_as_child(second_label));
	
	win_show(wtk_button_as_child(button_ok));
	win_show(wtk_button_as_child(button_cancel));
	win_show(dialogue_window);

	return dialogue_window;
	//											TODO: RYDDES!

error_widget:
	win_destroy(dialogue_window);
outofmem_win:
	membag_free(dialogue_struct);
outofmem_dialogue_struct:
	return NULL;
}

//! @}
