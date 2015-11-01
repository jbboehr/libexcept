
#include <stdio.h>

#include "except.h"

static __thread struct except_frame except_stack[128] = {0};
static __thread int except_stack_pos = 0;
static __thread int next_except;
static __thread struct except_frame * except_current = NULL;

struct except_frame * except_frame_ctor() {
	return &except_stack[++except_stack_pos];
}

struct except_frame * except_frame_top() {
	return &except_stack[except_stack_pos];
}

struct except_frame * except_frame_pop() {
	return &except_stack[except_stack_pos--];
}

void except_in(struct except_frame * frame) {
	except_current = frame;
}

void except_throw(int x, const char * s) {
	struct except_frame * frame = except_frame_top();

	if( except_stack_pos <= 0 ) {
		fprintf(stderr, "Uncaught %s\n", s);
		abort();
	}

	if( except_current && except_current->d ) {
		except_current->x = x;
		x = XFINALLY;
	}

	longjmp(&frame->buf, x);
}

