#!/bin/sh

# call with one argument - the path/file.bin (not .uf2) to upload using bossac

if ! [ $1 ]; then
   echo no args.  Exiting; fi
   ~/.arduino15/packages/arduino/tools/bossac/1.7.0/bossac \
    -i -d --port=/dev/ttyACM0 -U true -i -e -w -v ${1} -R  # .bin not .elf

exit 0

