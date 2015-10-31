
#include "except.h"

struct except_frame except_stack[128] = {0};
int except_stack_pos = 0;
int next_except;

struct except_frame * except_frame_ctor() {
	return &except_stack[++except_stack_pos];
}

struct except_frame * except_frame_top() {
	return &except_stack[except_stack_pos];
}

struct except_frame * except_frame_pop() {
	return &except_stack[except_stack_pos--];
}

struct except_frame * except_frame_pop_if_top(struct except_frame * frame) {
	if( frame == except_frame_top() ) {
		return except_frame_pop();
	} else {
		return NULL;
	}
}
void except_throw(int x, struct except_frame * cur) {
	struct except_frame * frame = except_frame_pop();
	if( cur->c ) {
		cur->x = x;
fprintf(stderr, "DEFERRING EXCEPTION\n");
	} else {
		longjmp(&frame->buf, x);
	}
}

