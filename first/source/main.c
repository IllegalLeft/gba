/*
 * main.c
 *
 * Copyright 2014 Samuel Volk <sam@Erdrick>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <gba_base.h>
#include <gba_video.h>
#include <gba_input.h>

#define vid_mem		((unsigned short*)VRAM)


void vid_vsync()
{
    while(REG_VCOUNT >= 160);   // wait till VDraw
    while(REG_VCOUNT < 160);    // wait till VBlank
}

int main()
{
	int color = 0;
	//int lastcolor = 0;

	// set mode 3, BG2 enabled
	REG_DISPCNT = MODE_3 | BG2_ENABLE;

	while (1)
	{
		// vertical sync
		vid_vsync();
		
		// set color
		color = REG_KEYINPUT;

		// y
		int i, j;
		for(j = 0; j < SCREEN_HEIGHT; j++)
		{
			for(i = 0; i < SCREEN_WIDTH; i++)
			{
				vid_mem[j*SCREEN_WIDTH + i] = color;
			}
		}
	}

	return 0;
}

