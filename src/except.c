
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

struct except_frame * except_frame_pop_if_top(struct except_frame * frame) {
	if( frame == except_frame_top() ) {
		return except_frame_pop();
	} else {
		return NULL;
	}
}

void except_in(struct except_frame * frame) {
	except_current = frame;
}

void except_throw(int x) {
	struct except_frame * frame = except_frame_top();
	if( except_current ) {
		except_current->x = x;
	} else {
		except_frame_pop();
		longjmp(&frame->buf, x);
	}
}

