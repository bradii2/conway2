#!/bin/bash

gcc -o run.exe ./src/*.c -ISDL2/include -LSDL2/lib -lSDL2main -lSDL2 -Wall