#!/bin/bash
lex lex.l
yacc -d par.y
gcc lex.yy.c -ll 
echo "Enter path to input file"
read path
echo "Reading path = $path"
./a.out < $path
