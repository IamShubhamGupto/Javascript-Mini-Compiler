%{
#include "lex.yy.c"	
%}

%token T_VAR T_DEF T_KEY T_ID T_NUM T_LBR T_RBR T_STR T_SHA T_LCG T_LOP T_OP1 T_OP2 T_OP3 T_OP4 T_WHILE T_FOR T_IF T_ELSE T_IN T_LET T_CONSOLE T_DOCUMENT
%start start

%%
start: seqOfStmts;

seqOfStmts: statement seqOfStmts | statement;

anyOperator: T_LCG | T_LOP | T_OP1 | T_OP2 | T_OP3;

terminator: ';' | '\n';



statement: declare terminator|expr terminator|for |while |if | '{'{scope[stop++]=sid++;} seqOfStmts '}' {stop--;} | T_CONSOLE '(' expr ')'| T_DOCUMENT '(' T_STR ')' ;

id: T_ID {mkentr(0,indentifier,scope[stop-1]);printf("updating :%s scope:%d\n",indentifier,scope[stop-1]);};

idV: T_ID {chkentr(indentifier);printf("checking :%s scope:%d\n",indentifier,scope[stop-1]);};

assign: '=' | T_SHA;

expr: id assign expr | value | ;

value: unit anyOperator value |unit;

unit: idV | T_OP4 idV | idV T_OP4 | T_STR {add_type_name(indentifier, 1);}| T_NUM {add_type_name(indentifier, 0);}| '(' list ')'| func | '[' list ']';

func: idV '(' list ')';

list: expr ',' list | expr;

declare: T_VAR mulDecl | T_LET mulDecl;

mulDecl: id |id ',' mulDecl|id '=' expr|id '=' expr ',' mulDecl;

varOperator: T_VAR | T_LET | ;

for: T_FOR '(' varOperator list ';' list ';' list ')' statement;

while: T_WHILE '(' expr ')' statement;

if: T_IF '(' expr ')' statement | ifelse;  

ifelse: T_ELSE statement;

%%



