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

#include "ws_factory.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INT_AS_STRING_LENGTH 15

/**
 * @return To not free the returned object.
 */
static b3_ws_t *
b3_ws_factory_ws_by_id(b3_ws_factory_t *ws_factory, const char *id);

b3_ws_factory_t *
b3_ws_factory_new(void)
{
	b3_ws_factory_t *ws_factory;

	ws_factory = NULL;
	ws_factory = malloc(sizeof(b3_ws_factory_t));

	array_new(&(ws_factory->ws_arr));

	ws_factory->ws_counter = b3_counter_new(1, 1);

	return ws_factory;
}

int
b3_ws_factory_free(b3_ws_factory_t *ws_factory)
{
	ArrayIter ws_iter;
	b3_ws_t *ws;

	array_iter_init(&ws_iter, ws_factory->ws_arr);
	while (array_iter_next(&ws_iter, (void *) &ws) != CC_ITER_END) {
		array_iter_remove(&ws_iter, NULL);
		b3_ws_free(ws);
	}
	array_destroy(ws_factory->ws_arr);
	ws_factory->ws_arr = NULL;

	b3_counter_free(ws_factory->ws_counter);
	ws_factory->ws_counter = NULL;

	free(ws_factory);
	return 0;
}


b3_ws_t *
b3_ws_factory_create(b3_ws_factory_t *ws_factory, const char *id)
{
	char *tmp_name;
	b3_ws_t *ws;

	tmp_name = NULL;

	if (id) {
	} else {
		tmp_name = malloc(sizeof(char) * INT_AS_STRING_LENGTH);
		snprintf(tmp_name, INT_AS_STRING_LENGTH, "%d", b3_counter_next(ws_factory->ws_counter));
		id = tmp_name;
	}

	ws = b3_ws_factory_ws_by_id(ws_factory, id);
	if (!ws) {
		ws = b3_ws_new(id);
	}

	if (tmp_name) {
		id = NULL;
		free(tmp_name);
	}

	return ws;
}

int
b3_ws_factory_remove(b3_ws_factory_t *ws_factory, const char *id)
{
	ArrayIter ws_iter;
	b3_ws_t *ws;
	char found;
	int ret;

	ws = NULL;
	found = 0;
	array_iter_init(&ws_iter, ws_factory->ws_arr);
	while (array_iter_next(&ws_iter, (void *) &ws) != CC_ITER_END
		   && !found) {
		if (strcmp(b3_ws_get_name(ws), id) == 0) {
			found = 1;
		}
	}

	ret = 1;
	if (found) {
		b3_ws_free(ws);
		ret = 0;
	}

	return ret;

}

b3_ws_t *
b3_ws_factory_ws_by_id(b3_ws_factory_t *ws_factory, const char *id)
{
	ArrayIter ws_iter;
	b3_ws_t *ws;
	char found;

	ws = NULL;
	found = 0;
	array_iter_init(&ws_iter, ws_factory->ws_arr);
	while (array_iter_next(&ws_iter, (void *) &ws) != CC_ITER_END
		   && !found) {
		if (strcmp(b3_ws_get_name(ws), id) == 0) {
			found = 1;
		}
	}

	if (!found) {
		ws = NULL;
	}

	return ws;
}
