#!/bin/bash

incDir="$(pwd)/inc"

gcc -g main.c -I${incDir} ${incDir}/**.c -o ../bin/main.o
