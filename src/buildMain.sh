#!/bin/bash

incDir="$(pwd)/inc"

${CROSS_COMPILE}gcc -static main.c -I${incDir} ${incDir}/**.c -o ../bin/main.o
