#
# Makefile for the FREAX-kernel character device drivers.
#
# Note! Dependencies are done automagically by 'make dep', which also
# removes any old dependencies. DON'T put your own dependencies here
# unless it's something special (ie not a .c file).
#
include ../../Rules.make

LDFLAGS	= -x
CFLAGS	= -g -Wall -fstrength-reduce -fomit-frame-pointer \
	-finline-functions -nostdinc -fno-builtin -I../../include
CPP	+= -E -I../../include

.c.s:
	$(CC) $(CFLAGS) \
	-S -o $*.s $<
.s.o:
	$(AS) -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) \
	-c -o $*.o $<

OBJS  = tty_io.o console.o keyboard.o serial.o rs_io.o \
	tty_ioctl.o pty.o

chr_drv.a: $(OBJS)
	$(AR) rcs chr_drv.a $(OBJS)
	@sync

keyboard.s: keyboard.S
	$(CPP) -traditional keyboard.S -o keyboard.s

clean:
	rm -f core *.o *.a tmp_make keyboard.s
	for i in *.c;do rm -f `basename $$i .c`.s;done

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do echo -n `echo $$i | sed 's,\.c,\.s,'`" "; \
		$(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile

### Dependencies:
console.s console.o : console.c ../../include/os/sched.h   ../../include/os/head.h ../../include/os/fs.h   ../../include/sys/types.h ../../include/os/mm.h   ../../include/os/kernel.h ../../include/signal.h   ../../include/sys/param.h ../../include/sys/time.h ../../include/time.h   ../../include/sys/resource.h ../../include/os/tty.h   ../../include/termios.h ../../include/os/config.h ../../include/asm/io.h   ../../include/asm/system.h ../../include/asm/segment.h   ../../include/string.h ../../include/errno.h
pty.s pty.o : pty.c ../../include/os/tty.h ../../include/termios.h   ../../include/sys/types.h ../../include/os/sched.h   ../../include/os/head.h ../../include/os/fs.h   ../../include/os/mm.h ../../include/os/kernel.h   ../../include/signal.h ../../include/sys/param.h ../../include/sys/time.h   ../../include/time.h ../../include/sys/resource.h   ../../include/asm/system.h ../../include/asm/io.h
serial.s serial.o : serial.c ../../include/os/tty.h ../../include/termios.h   ../../include/sys/types.h ../../include/os/sched.h   ../../include/os/head.h ../../include/os/fs.h   ../../include/os/mm.h ../../include/os/kernel.h   ../../include/signal.h ../../include/sys/param.h ../../include/sys/time.h   ../../include/time.h ../../include/sys/resource.h   ../../include/asm/system.h ../../include/asm/io.h
tty_io.s tty_io.o : tty_io.c ../../include/ctype.h ../../include/errno.h   ../../include/signal.h ../../include/sys/types.h ../../include/unistd.h   ../../include/sys/stat.h ../../include/sys/time.h ../../include/time.h   ../../include/sys/times.h ../../include/sys/utsname.h   ../../include/sys/param.h ../../include/sys/resource.h   ../../include/utime.h ../../include/os/sched.h   ../../include/os/head.h ../../include/os/fs.h   ../../include/os/mm.h ../../include/os/kernel.h   ../../include/os/tty.h ../../include/termios.h   ../../include/asm/segment.h ../../include/asm/system.h
tty_ioctl.s tty_ioctl.o : tty_ioctl.c ../../include/errno.h ../../include/termios.h   ../../include/sys/types.h ../../include/os/sched.h   ../../include/os/head.h ../../include/os/fs.h   ../../include/os/mm.h ../../include/os/kernel.h   ../../include/signal.h ../../include/sys/param.h ../../include/sys/time.h   ../../include/time.h ../../include/sys/resource.h ../../include/os/tty.h   ../../include/asm/io.h ../../include/asm/segment.h   ../../include/asm/system.h

