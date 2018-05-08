#!/bin/bash

gcc -o run.o ./src/*.c -ISDL2/include -LSDL2/lib -lSDL2main -lSDL2 -Wall -m64 -g