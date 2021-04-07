CC=gcc
RM=rm
# compiler: lex.yy.c header.h
# 	$(CC) lex.yy.c -ll -ly -o asticg
compiler: lex.yy.c header.h
	$(CC) lex.yy.c -ll -o asticg

lex.yy.c: y.tab.c lex.l
	lex lex.l

y.tab.c: par.y
	yacc -d par.y

clean:
	$(RM) lex.yy.c asticg y.tab.c y.tab.h
