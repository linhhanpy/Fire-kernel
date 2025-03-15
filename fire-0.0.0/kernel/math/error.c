/*
 * fire/kernel/math/error.c
 *
 *  (C) 2025 Lin Honghan
 */

#include <signal.h>

#include <os/sched.h>

void math_error(void)
{
	__asm__("fnclex");
	if (last_task_used_math)
		last_task_used_math->signal |= 1<<(SIGFPE-1);
}
