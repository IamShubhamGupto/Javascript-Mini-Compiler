%{
	
	int yyparse(void);
	int yylex(void);
	int yywrap(void);
	void yyerror(const char *);
	void addTokenToFile(const char *t, const char *s);
	int scs[100]={0};
	int stop=1;
	int sid=1;
	int elno=1;
	int lbl=0;
	int tmp=0;
	char *identifier;
	char bbuf[1000];
	char ysign[10];

	#include <string.h>
	#include "header.h"
	#include "y.tab.c"
	#include "y.tab.h"
%}
%option nounput
%option noinput
%%
\/\*([^*]|\*[^/])*\*\/			;
\/\/[^\n]*						;
var 				{return T_VAR;}
def 				{return T_DEF;}
if					{return T_IF; }
else				{return T_ELSE;}
in					{return T_IN;}
let					{return T_LET;}
while 				{return T_WHILE;};
console.log			{return T_CONSOLE;}
document.write		{return T_DOCUMENT;}
break|case|catch|continue|debugger|default|delete|do|else|finally|function|if|in|instanceof|new|return|switch|this|throw|try|typeof|var|void|with		  {return T_KEY;}
([a-zA-Z]|\_)([a-zA-Z0-9]|\_)* 		{identifier=strdup(yytext);return T_ID;}
[0-9]+(\.[0-9]+)?(E[-+]?[0-9]+)? 	{mkentr(2,yytext,0);return T_NUM;}

[\[\(\{]			{return yytext[0];}
[\]\)\}]			{return yytext[0];}

\"([^"]|\\\")*\"|\'([^']|\\\')*\' 	{mkentr(1,yytext,0);return T_STR;}

=					{return '=';}
\.					{return '.';}
[+\-*/^&|]=			{return T_SHA;}
(&&|\|\|)			{strcpy(ysign,yytext);return T_LCG;}
([<>]|==)=?			{strcpy(ysign,yytext);return T_LOP;}
,					{return ',';}
[+-]				{strcpy(ysign,yytext);return T_OP1;}
[*/^&|]				{strcpy(ysign,yytext);return T_OP2;}
\*\*				{strcpy(ysign,yytext);return T_OP3;}
(\+\+|\-\-)			{return T_OP4;}
;					{return ';';}
[\n]				{elno++;return '\n';}
[\t ]	            ;	

%%

void addTokenToFile(const char *t, const char *s){

	FILE *fptr;
	fptr = fopen("tokens.txt", "a");
	if(fptr == NULL){
		printf("Error!");
		exit(1);
   	}
	
	#if 0
	printf("+++++++ %s %d ++++++\n",t,strlen(s));
	#endif
	fprintf(fptr,"%s : %s\n", t, s);
	#if 1
	if(strlen(s) == 1){
		fprintf(fptr,"ASCII value of %s : %d\n", s,s[0]);
	}
	#endif
	fclose(fptr);
}

void yyerror(const char *a)
{
	printf("[yyerror]\nError in line %d, %s\n", elno,a);
	return;
}
int yywrap(void){
	return 1;
}
int main(int argc, char *argv[]){
	
	if(argc == 2){
		yyin = fopen(argv[1],"r");
	}
	yyparse();
	// printall();
	return 0;
}
//printf("*************\n************\nafter %d line , symbol table is\n", elno-1);printall();