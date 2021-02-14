%{ 
#include <stdio.h>
int line_number = 1;   
%} 
  
%% 
.*\n { fprintf(yyout, "%2d %s", line_number++, yytext); }  
%% 
  
int yywrap(){
	return 1;
}  
  
int main(int argc, char*argv[]) 
{ 
	if(argc == 2){
		yyin = fopen(argv[1],"r");
	} 
	yyout = fopen("number.txt", "w");
	yylex(); 
	
	return 0; 
} 
