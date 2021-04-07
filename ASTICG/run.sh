#!/bin/bash
lex lex.l
yacc -d par.y
gcc lex.yy.c header.h -ll -o asticg
gcc y.tab.c header.h
./a.out < inputFiles/input4.js
