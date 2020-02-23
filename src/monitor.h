/******************************************************************************
  This file is part of b3.

  Copyright 2020 Richard Paul Baeck <richard.baeck@mailbox.org>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*******************************************************************************/

/**
 * @author Richard B�ck
 * @date 2020-02-16
 * @brief File contains the monitor definition
 */

#include <collectc/array.h>
#include <windows.h>

#include "bar.h"
#include "ws_factory.h"

#ifndef MONITOR_H
#define MONITOR_H

typedef struct b3_monitor_s
{
	char *monitor_name;

	RECT monitor_area;

	b3_bar_t *bar;

	b3_ws_factory_t *ws_factory;

	/**
	 * Array of char *
	 */
	Array *wsid_arr;
} b3_monitor_t;

/**
 * @brief Creates a new monitor object
 * @param monitor_name A string object. It will be copied.
 * @param monitor_area The rectangle of the work area
 * @param ws_factory A workspace factory object. It will not be freed by the monitor.
 * @return A new monitor object or NULL if allocation failed
 */
extern b3_monitor_t *
b3_monitor_new(const char *monitor_name, RECT monitor_area, b3_ws_factory_t *ws_factory);

/**
 * @brief Frees a monitor object
 * @return Non-0 if the freeing failed
 */
extern int
b3_monitor_free(b3_monitor_t *ws);

extern const char *
b3_monitor_get_monitor_name(b3_monitor_t *ws);

extern RECT
b3_ws_get_monitor_area(b3_monitor_t *ws);

extern const b3_bar_t *
b3_monitor_get_bar(b3_monitor_t *ws);

extern int
b3_monitor_show(b3_monitor_t *monitor);

extern int
b3_monitor_draw(b3_monitor_t *ws, HWND window_handler);

#endif // MONITOR_H