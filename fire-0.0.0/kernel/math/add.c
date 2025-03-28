/*
 *  fire/kernel/math/add.c
 *
 *  (C) 2025 Lin Honghan
 */

#include <os/math_emu.h>

#define NEGINT(a) \
__asm__("notl %0 ; notl %1 ; addl $1,%0 ; adcl $0,%1" \
	:"=r" (a->a),"=r" (a->b) \
	:"0" (a->a),"1" (a->b))

static void signify(temp_real * a)
{
	a->exponent += 2;
	__asm__("shrdl $2,%1,%0 ; shrl $2,%1"
		:"=r" (a->a),"=r" (a->b)
		:"0" (a->a),"1" (a->b));
	if (a->exponent < 0)
		NEGINT(a);
	a->exponent &= 0x7fff;
}

static void unsignify(temp_real * a)
{
	if (!(a->a || a->b)) {
		a->exponent = 0;
		return;
	}
	a->exponent &= 0x7fff;
	if (a->b < 0) {
		NEGINT(a);
		a->exponent |= 0x8000;
	}
	while (a->b >= 0) {
		a->exponent--;
		__asm__("addl %0,%0 ; adcl %1,%1"
			:"=r" (a->a),"=r" (a->b)
			:"0" (a->a),"1" (a->b));
	}
}

void fadd(const temp_real * src1, const temp_real * src2, temp_real * result)
{
	temp_real a,b;
	int x1,x2,shift;

	x1 = src1->exponent & 0x7fff;
	x2 = src2->exponent & 0x7fff;
	if (x1 > x2) {
		a = *src1;
		b = *src2;
		shift = x1-x2;
	} else {
		a = *src2;
		b = *src1;
		shift = x2-x1;
	}
	if (shift >= 64) {
		*result = a;
		return;
	}
	if (shift >= 32) {
		b.a = b.b;
		b.b = 0;
		shift -= 32;
	}
	__asm__("shrdl %4,%1,%0 ; shrl %4,%1"
		:"=r" (b.a),"=r" (b.b)
		:"0" (b.a),"1" (b.b),"c" ((char) shift));
	signify(&a);
	signify(&b);
	__asm__("addl %4,%0 ; adcl %5,%1"
		:"=r" (a.a),"=r" (a.b)
		:"0" (a.a),"1" (a.b),"g" (b.a),"g" (b.b));
	unsignify(&a);
	*result = a;
}
