#!/bin/bash

incDir="$(pwd)/inc"
ofname="tp1main.o"

${CROSS_COMPILE}gcc -static main.c -I${incDir} ${incDir}/**.c -o ../bin/${ofname}

if [ -n "$1" ]; then
 cp ../bin/${ofname} $1
fi
