/* Copyright (C) 2009-2015 Francesco Nidito 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions: 
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. 
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 */

#ifndef _TRY_THROW_CATCH_H_
#define _TRY_THROW_CATCH_H_

#include <stdio.h>
#include <setjmp.h>

/* For the full documentation and explanation of the code below, please refer to
 * /~nids/docs/longjump_try_trow_catch.html
 */

#define \
	TRY do { \
		volatile struct except_frame * ex_frame__ = except_frame_ctor(); \
		ex_frame__->x = 0; \
		ex_frame__->r = setjmp(&ex_frame__->buf); \
		switch( ex_frame__->r ) { \
			case 0: while(1) {

#define CATCH(x) \
				break; \
				case x: \
					ex_frame__->c = 1;

#define FINALLY \
					ex_frame__->c = 0; \
				break; \
			} default: {

#define ETRY \
					ex_frame__->c = 0; \
				break; \
			} \
		} \
		if( ex_frame__->x ) { \
			THROW(ex_frame__->x); \
		} \
	} while(0) \

#define THROW(z) \
	except_throw(z, ex_frame__); \
	fprintf(stderr, "ARGGG\n");\
	if( ex_frame__->x ) { \
		break; \
	}

struct except_frame {
	jmp_buf buf;
	int x;
	int r;
	int c;
};

struct except_frame * except_frame_ctor();
struct except_frame * except_frame_top();
struct except_frame * except_frame_pop();
struct except_frame * except_frame_pop_if_top(struct except_frame * frame);
void except_throw(int x, struct except_frame * cur);

#endif /*!_TRY_THROW_CATCH_H_*/
