include ../Rules.make

CFLAGS	= -g -Wall -fstrength-reduce -fomit-frame-pointer \
	-finline-functions -nostdinc -fno-builtin -I../include

CPP	+= -E -I../include

.c.o:
	$(CC) $(CFLAGS) \
	-c -o $*.o $<
.s.o:
	$(AS) -o $*.o $<
.c.s:
	$(CC) $(CFLAGS) \
	-S -o $*.s $<

OBJS	= memory.o swap.o page.o

all: mm.o

mm.o: $(OBJS)
	$(LD) -r -o mm.o $(OBJS)

clean:
	rm -f core *.o *.a tmp_make
	for i in *.c;do rm -f `basename $$i .c`.s;done

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in *.c;do $(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile

### Dependencies:
memory.o : memory.c ../include/signal.h ../include/sys/types.h \
  ../include/asm/system.h ../include/os/sched.h ../include/os/head.h \
  ../include/os/fs.h ../include/os/mm.h ../include/os/kernel.h \
  ../include/sys/param.h ../include/sys/time.h ../include/time.h \
  ../include/sys/resource.h 
swap.o : swap.c ../include/string.h ../include/os/sched.h \
  ../include/os/head.h ../include/os/fs.h ../include/sys/types.h \
  ../include/os/mm.h ../include/os/kernel.h ../include/signal.h \
  ../include/sys/param.h ../include/sys/time.h ../include/time.h \
  ../include/sys/resource.h 
