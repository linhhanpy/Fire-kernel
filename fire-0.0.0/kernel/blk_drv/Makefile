#
# Makefile for the FREAX-kernel block device drivers.
#
# Note! Dependencies are done automagically by 'make dep', which also
# removes any old dependencies. DON'T put your own dependencies here
# unless it's something special (ie not a .c file).
#
include ../../Rules.make

LDFLAGS	= -x
CFLAGS	= -g -Wall -fstrength-reduce -fomit-frame-pointer \
	-finline-functions  -nostdinc -fno-builtin -I../../include
CPP	+= -E -I../../include

.c.s:
	$(CC) $(CFLAGS) \
	-S -o $*.s $<
.s.o:
	$(AS) -c -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) \
	-c -o $*.o $<

OBJS  = ll_rw_blk.o floppy.o hd.o ramdisk.o

blk_drv.a: $(OBJS)
	$(AR) rcs blk_drv.a $(OBJS)
	@sync

clean:
	rm -f core *.o *.a tmp_make
	for i in *.c;do rm -f `basename $$i .c`.s;done

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do echo -n `echo $$i | sed 's,\.c,\.s,'`" "; \
		$(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile

### Dependencies:
floppy.s floppy.o : floppy.c ../../include/os/sched.h ../../include/os/head.h   ../../include/os/fs.h ../../include/sys/types.h ../../include/os/mm.h   ../../include/os/kernel.h ../../include/signal.h   ../../include/sys/param.h ../../include/sys/time.h ../../include/time.h   ../../include/sys/resource.h ../../include/os/fdreg.h   ../../include/asm/system.h ../../include/asm/io.h   ../../include/asm/segment.h blk.h
hd.s hd.o : hd.c ../../include/os/config.h ../../include/os/sched.h   ../../include/os/head.h ../../include/os/fs.h   ../../include/sys/types.h ../../include/os/mm.h   ../../include/os/kernel.h ../../include/signal.h   ../../include/sys/param.h ../../include/sys/time.h ../../include/time.h   ../../include/sys/resource.h ../../include/os/hdreg.h   ../../include/asm/system.h ../../include/asm/io.h   ../../include/asm/segment.h blk.h
ll_rw_blk.s ll_rw_blk.o : ll_rw_blk.c ../../include/errno.h ../../include/os/sched.h   ../../include/os/head.h ../../include/os/fs.h   ../../include/sys/types.h ../../include/os/mm.h   ../../include/os/kernel.h ../../include/signal.h   ../../include/sys/param.h ../../include/sys/time.h ../../include/time.h   ../../include/sys/resource.h ../../include/asm/system.h blk.h
ramdisk.s ramdisk.o : ramdisk.c ../../include/string.h ../../include/os/config.h   ../../include/os/sched.h ../../include/os/head.h   ../../include/os/fs.h ../../include/sys/types.h ../../include/os/mm.h   ../../include/os/kernel.h ../../include/signal.h   ../../include/sys/param.h ../../include/sys/time.h ../../include/time.h   ../../include/sys/resource.h ../../include/asm/system.h   ../../include/asm/segment.h ../../include/asm/memory.h blk.h
