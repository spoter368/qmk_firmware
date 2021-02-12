/* Copyright 2021 spoter368
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "corbit.h"
#include "split_util.h"

void matrix_init_kb(void) {
	// overrides default __weak option in matrix_common.c
	// put your keyboard start-up code here
	// runs once when the firmware starts up
	
	// Initialize indicator LEDs to output based on if it's left or right hand
	if (isLeftHand)
	{
		setPinOutput(C6);
		setPinOutput(B6);
		setPinOutput(B5);
		//DDRC |= (1<<6);
		//DDRB |= (1<<6);
		//DDRB |= (1<<5);
	}
	else
	{
		setPinOutput(F6);
		setPinOutput(F7);
		setPinOutput(C7);
		//DDRF |= (1<<6);
		//DDRF |= (1<<7);
		//DDRC |= (1<<7);
	}
	
	//gotta call this even though there's nothin in it
	matrix_init_user();
}



bool led_update_kb(led_t led_state) {
	// overrides default led_update_kb that normally parses config.h options
	// must do this bc each half has different pins
	
	// led_update_user returns 1 if the user level wants the kb level to run.
	// by default it's a __weak function that returns true
    bool res = led_update_user(led_state);
    if(res) {
		
		if (isLeftHand)
		{
			setPinOutput(C6);
			setPinOutput(B6);
			setPinOutput(B5);
			writePin(B5, led_state.num_lock);
			writePin(B6, led_state.caps_lock);
			writePin(C6, led_state.scroll_lock);
		}
		else
		{
			setPinOutput(F6);
			setPinOutput(F7);
			setPinOutput(C7);
			writePin(F6, led_state.num_lock);
			writePin(F7, led_state.caps_lock);
			writePin(C7, led_state.scroll_lock);
		}



    }
	
	// returned val does nothing right now
    return res;
}