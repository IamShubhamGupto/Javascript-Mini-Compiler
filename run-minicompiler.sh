#!/bin/bash
lex lexer.l
yacc -d parser.y
gcc y.tab.c
./a.out < input1.txt
