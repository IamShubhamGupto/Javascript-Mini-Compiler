%{
int yyparse(void);
int yylex(void);
void yyerror(char *);
int scope[100]={0},stop=1,sid=1, elno=1;
char *indentifier;
#include<string.h>
#include"stbls.h"
#include"y.tab.h"
void yyerror(char *a){printf("\nError in line %d, %s\n", elno,a);return;}
void addTokenToFile(char *t, char *s);
int main(int argc, char *argv[]){
	
	if(argc == 2){
		yyin = fopen(argv[1],"r");
	}
	yyparse();
	printall();
	return 0;
}

%}

%%

\/\*([^*]|\*[^/])*\*\/			;
\/\/[^\n]*				;
var 				{addTokenToFile("Type",yytext);return T_VAR;}
def 				{addTokenToFile("Function", yytext);return T_DEF;}
if					{addTokenToFile("Keyword",yytext);return T_IF; }
else				{addTokenToFile("Keyword",yytext);return T_ELSE;}
in					{addTokenToFile("Keyword",yytext);return T_IN;}
let					{addTokenToFile("Keyword",yytext);return T_LET;}
for					{addTokenToFile("Keyword",yytext);return T_FOR;}
while					{addTokenToFile("Keyword",yytext);return T_WHILE;}
console.log			{addTokenToFile("Print", yytext);return T_CONSOLE;}
document.write		{addTokenToFile("Print", yytext);return T_DOCUMENT;}
break|case|catch|continue|debugger|default|delete|do|else|finally|for|function|if|in|instanceof|new|return|switch|this|throw|try|typeof|var|void|with|while				{addTokenToFile("Keyword", yytext);return T_KEY;}
([a-zA-Z]|\_)([a-zA-Z0-9]|\_)* 		{indentifier=strdup(yytext);addTokenToFile("Identifer", yytext);return T_ID;}
[0-9]+(\.[0-9]+)?(E[-+]?[0-9]+)? 	{mkentr(2,yytext,0);addTokenToFile("Number", yytext);return T_NUM;}

[\[\(\{]			{addTokenToFile("Open Brackets", yytext); return yytext[0];}
[\]\)\}]			{addTokenToFile("Close Brackets", yytext);return yytext[0];}

\"([^"]|\\\")*\"|\'([^']|\\\')*\' 	{mkentr(1,yytext,0);addTokenToFile("String", yytext);return T_STR;}

=					{addTokenToFile("Equals", yytext);return '=';}
\.					{addTokenToFile("Dot", yytext);return '.';}
[+\-*/^&|]=			{addTokenToFile("ShortHand", yytext);return T_SHA;}
(&&|\|\|)			{addTokenToFile("Logical Operators", yytext);return T_LCG;}
([<>]|==)=?			{addTokenToFile("Equality", yytext);return T_LOP;}
,					{addTokenToFile("Comma", yytext);return ',';}
[+-]				{addTokenToFile("Op1", yytext);return T_OP1;}
[*/^&|]				{addTokenToFile("Op2", yytext);return T_OP2;}
\*\*				{addTokenToFile("Op3", yytext);return T_OP3;}
(\+\+|\-\-)			{addTokenToFile("Op4", yytext);return T_OP4;}
;					{addTokenToFile("Colon", ";");return ';';}
[\n]				{elno++;}
[\t ]	            {printf("");}	

%%


void addTokenToFile(char *t, char *s){
   	FILE *fptr;
   	
   	fptr = fopen("tokens.txt", "a");
   	if(fptr == NULL)
   	{
      printf("Error!");
      exit(1);
   	}

   	fprintf(fptr,"%s : %s\n", t, s);
   	fclose(fptr);
}

