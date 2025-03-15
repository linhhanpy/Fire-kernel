#!/bin/sh
export OSLAB_PATH=$(dirname `which $0`)

if [ ! -e "hdc.img" ]; then
    tar -xvJf hdc.tar.xz
fi

if [ "$1" ] && [ "$1" = "-m" ]
then
    (cd ../fire-0.0.0; make clean; make; cp Image ../oslab/Image)
elif [ "$1" ] && [ "$1" = "-qemu" ]
then
    qemu-system-x86_64 \
        -m 32 \
        -vga cirrus \
        -drive file="$OSLAB_PATH/Image",format=raw,if=floppy,index=0 \
        -drive file="$OSLAB_PATH/hdc.img",format=raw,if=ide,index=0 \
        -boot a \
        -serial file:"$OSLAB_PATH/bochsout.txt" \
        -cpu qemu64 \
        -smp 1 \
        -M pc
elif [ "$1" ] && [ "$1" = "-g" ]
then
    $OSLAB_PATH/bochs/bochs-gdb -q -f $OSLAB_PATH/bochs/bochsrc-gdb.bxrc & \
    gdb -x $OSLAB_PATH/bochs/.gdbrc ../fire-0.0.0/tools/system
else
    bochs -q -f $OSLAB_PATH/bochs/bochsrc.bxrc
fi