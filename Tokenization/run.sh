#!/bin/bash

lex lexer.l
yacc -d parser.y
gcc y.tab.c -Wall

FILE=a.out

if test -f "$FILE"; then
    echo "Enter path to input file"
    read path
    echo "Reading path = $path"
    ./a.out < $path
else
    echo "Error during compilation!! Exiting..."
fi


