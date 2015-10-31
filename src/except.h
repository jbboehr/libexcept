
#ifndef EXCEPT_H
#define EXCEPT_H

#include <stdio.h>
#include <setjmp.h>

#define TRY \
	do { \
		volatile struct except_frame * ex_frame__ = except_frame_ctor(); \
		ex_frame__->r = setjmp(&ex_frame__->buf); \
		switch( ex_frame__->r ) { \
			case 0: 

#define CATCH(x) \
				except_in(NULL); \
			break; \
			case x: \
				except_in(ex_frame__); \

#define FINALLY \
				except_in(NULL); \
			break; \
	} \
	switch(0) { \
			default:

#define ETRY \
			break; \
		} \
		if( ex_frame__->x ) { \
			except_in(NULL); \
			THROW(ex_frame__->x); \
		} \
	} while(0) \

#define THROW(z) \
	except_throw(z); \
	if( ex_frame__->x ) { \
		break; \
	}

struct except_frame {
	jmp_buf buf;
	int x;
	short r;
	short c;
};

struct except_frame * except_frame_ctor();
struct except_frame * except_frame_top();
struct except_frame * except_frame_pop();
struct except_frame * except_frame_pop_if_top(struct except_frame * frame);
void except_in(struct except_frame * frame);
void except_throw(int x);

#endif /* EXCEPT_H */

