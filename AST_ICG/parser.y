%{
	#include <stdio.h>	
	#include <string.h>
	#include <stdlib.h>
	int yylex();
%}

%union
{
	struct {
		char* code;
		char* ast;
		int next;
		} stt;
	struct {
		char* code;
		char* ast;
		int idn;
		} eq;
	struct {
		int dt[4];
		} dt;
	struct {
		char* code;
		char* ast;
		int idn;
		int off;
	} ls;
}

%type<stt> seq statement for if while
%type<eq> expr unit defn anyopl anyoph rhsl rhsh 
%type<ls> list
%type<dt> lhs lhsv edt
%token T_VAR T_DEF T_KEY T_ID T_NUM T_LBR T_RBR T_STR T_SHA T_LCG T_LOP T_OP1 T_OP2 T_OP3 T_OP4 T_FOR T_WHILE T_IF T_ELSE T_IN T_LET
%start start
%left '+' '-'
%left '*' '/'
%%
start:
	seq
	{
		FILE *f; f=fopen("icg.txt","w");
		printf("\n\nast generated:\n\n%s\n\ncode generated:\n\n%s", $1.ast,$1.code);
		fprintf(f,"%s",$1.code);
		fclose(f);
	};

edt: ;

anyopl:T_LOP 
{
	// char* a;
	// if(strcmp(ysign,">")){
	// 	$$.code=strdup("gt");
	// }
	// else if(strcmp(ysign,"<")){
	// 	$$.code=strdup("lt");
	// }else{
	// 	$$.code=strdup(ysign);
	// }
	
	$$.code=strdup(ysign);
}
|
T_OP1 
{
	$$.code=strdup(ysign);
}
|
T_LCG {
	$$.code=strdup(ysign);
};

anyoph:T_OP2 
{
	$$.code=strdup(ysign);
}
|
T_OP3 {
	$$.code=strdup(ysign);
};

adlm:';'|'\n';

seq:
	statement seq
		{
			$$.code = ap($1.code,$2.code);
			$$.ast = ap3($1.ast,strdup("\n"),$2.ast);
		}
		|
		{
			$$.code=strdup("");
			$$.ast=strdup("");
		};

statement:
	defn adlm 
	{
		$$.code=$1.code;
		$$.ast=$1.ast;
	}
	|
	expr adlm 
	{
		$$.code=$1.code;
		$$.ast=$1.ast;
	}
	|
	for 
	{
		$$.code=$1.code;
		$$.ast=$1.ast;
	}
	|
	if 
	{
		$$.code=$1.code;
		$$.ast=$1.ast;
	}
	|
	while
	{
		$$.code=$1.code;
		$$.ast=$1.ast;
	}
	|
	'{'
		{scs[stop++]=sid++;} 
		seq 
	'}' {stop--;}
	adlm  
	{
		$$.code=$3.code;
		$$.ast=ap3(strdup("{"),$3.ast,strdup("} "));
	}
	|
	adlm 
	{
		$$.code=strdup("");
		$$.ast=strdup("");
	};

lhs:T_ID 
{
	int v=mkentr(0,ygbl,scs[stop-1]);
	$$.dt[0]=v;
};

lhsv:T_ID 
{
	int v=chkentr(ygbl);
	if(v==-1)
	{
		printf("variable not found\n");
		exit(0);
	}
	$$.dt[0]=v;
};

eqb:'='|T_SHA;

expr:lhs eqb expr
{
	char *a;
	sprintf(bbuf,"\t%s = t%d;\n",a=getname($1.dt[0]),$3.idn);
	$$.code=ap($3.code,strdup(bbuf));
	$$.idn=$3.idn;
	sprintf(bbuf,"\t%s = (",a);
	$$.ast=ap3(strdup(bbuf),$3.ast,strdup(")"));
}
|
rhsl {
	$$.code=$1.code;
	$$.idn=$1.idn;
	$$.ast=$1.ast;
}
;



rhsl:rhsh anyopl rhsl 
{
	int k=tmp++;
	sprintf(bbuf,"\tt%d = t%d %s t%d;\n",k,$1.idn,$2.code,$3.idn);
	$$.code=ap3($1.code,$3.code,strdup(bbuf));
	$$.idn=k;
	$$.ast=ap3(ap3(strdup(" ("),$1.ast,strdup(") ")),$2.code,ap3(strdup(" ("),$3.ast,strdup(") ")));free($2.code);
}
|
rhsh 
{
	$$.code=$1.code;
	$$.idn=$1.idn;
	$$.ast=$1.ast;
};

rhsh:unit anyoph rhsh 
{
	int k=tmp++;
	sprintf(bbuf,"\tt%d = t%d %s t%d;\n",k,$1.idn,$2.code,$3.idn);
	$$.code=ap3($1.code,$3.code,strdup(bbuf));
	$$.idn=k;
	$$.ast=ap3(ap3(strdup(" ("),$1.ast,strdup(") ")),$2.code,ap3(strdup(" ("),$3.ast,strdup(") ")));free($2.code);
}
|
unit 
{
	$$.code=$1.code;
	$$.idn=$1.idn;
	$$.ast=$1.ast;
};

unit: lhsv 
{
	char *a;
	int k=tmp++;
	sprintf(bbuf,"\tt%d = %s;\n",k,a=getname($1.dt[0]));
	$$.code=strdup(bbuf);
	$$.idn=k;$$.ast=strdup(a);
}
|	
T_OP4 lhsv |lhsv T_OP4|T_STR 
{
	int k=tmp++;
	add_type_name(ygbl, 1);
	sprintf(bbuf,"\tt%d = %s;\n",k,yytext);
	$$.code=strdup(bbuf);
	$$.idn=k;
	$$.ast=strdup(yytext);
}
|
T_NUM 
{	
	int k=tmp++;
	add_type_name(ygbl, 0);
	sprintf(bbuf,"\tt%d = %s;\n",k,yytext);
	$$.code=strdup(bbuf);
	$$.idn=k;$$.ast=strdup(yytext);
}
|
'[' list ']' 
{
	$$.code=$2.code;
	$$.idn=$2.idn;
	add_type_name(ygbl, 2);
	$$.ast=ap3(strdup(" ["),$2.ast,strdup("] "));
}
|
lhsv '[' expr ']' 
{	
	char *a;
	int k=tmp++;
	$$.idn=tmp++;
	sprintf(bbuf,"\tt%d = %s\nt%d=t%d[t%d];\n",k,a=getname($1.dt[0]),$$.idn,k,$3.idn);
	$$.code=ap($3.code,strdup(bbuf));
	sprintf(bbuf,"\t %s[",a);
	$$.ast=ap3(strdup(bbuf),$3.ast,strdup("] "));
};

func:lhsv '(' list ')';

list: list ',' expr 
{
	sprintf(bbuf,"\tt%d[%d]=t%d;\n",$1.idn,$1.off+1,$3.idn);
	$$.code=ap3($1.code,$3.code,strdup(bbuf));
	$$.off=$1.off+1;
	$$.idn=$1.idn;
	$$.ast=ap3($1.ast,strdup(","),$3.ast);
}
|
expr 
{
	$$.idn=tmp++;
	$$.off=0;
	sprintf(bbuf,"\tt%d[%d]=t%d;\n",$$.idn,$$.off,$1.idn);
	$$.code=ap($1.code,strdup(bbuf));
	$$.ast=$1.ast;
}
|
{
	$$.code=strdup("");
	$$.idn=tmp++;
	$$.ast=strdup("");
};

defn: T_VAR vtail|T_LET vtail;

vtail:lhs |lhs ',' vtail|lhs '=' expr|lhs '=' expr ',' vtail;

varop:T_VAR|T_LET|;

for: T_FOR edt 
{
	$2.dt[0]=lbl++;
	$2.dt[1]=lbl++;
} 
'(' expr ';' expr ';' expr ')' statement 
{
	char* a;
	char* b;
	sprintf(bbuf,"label l%d :\n",$2.dt[0]);
	a=ap3($5.code,strdup(bbuf),$7.code);
	sprintf(bbuf,"\tiffalse t%d goto l%d;\n",$7.idn,$2.dt[1]);
	b=ap3(strdup(bbuf),$11.code,$9.code);
	sprintf(bbuf,"\tgoto l%d;\nlabel l%d :\n",$2.dt[0],$2.dt[1]);
	$$.code=ap3(a,b,strdup(bbuf));
	a=ap3(strdup("for ("),$5.ast,strdup(";"));
	a=ap3(a,$7.ast,strdup(";"));
	a=ap3(a,$9.ast,strdup(")"));
	$$.ast=ap(a,$11.ast);
};
while: T_WHILE edt
{
	$2.dt[0]=lbl++;
	$2.dt[1]=lbl++;
}
'(' expr ')' statement
{
	//fixed maybe
	char* a;
	char* b;
	sprintf(bbuf,"label l%d :\n",$2.dt[0]);
	a=ap(strdup(bbuf),$5.code);
	sprintf(bbuf,"\tiffalse t%d goto l%d;\n",$5.idn,$2.dt[1]);
	b=ap(strdup(bbuf),$7.code);
	sprintf(bbuf,"\tgoto l%d;\nlabel l%d :\n",$2.dt[0],$2.dt[1]);
	$$.code=ap3(a,b,strdup(bbuf));
	a=ap3(strdup("while ("),$5.ast,strdup(")"));
	$$.ast=ap(a,$7.ast);
};

if : T_IF '('expr')' edt 
{
	$5.dt[0]=lbl++;
	$5.dt[1]=lbl++;
	$5.dt[2]=lbl++;
}
statement T_ELSE statement 
{
	char* a;
	char* b;
	sprintf(bbuf,"\tiftrue t%d goto l%d;\n\tgoto l%d;\nlabel l%d :\n",$3.idn,$5.dt[0],$5.dt[1],$5.dt[0]);
	a=ap3($3.code,strdup(bbuf),$7.code);
	sprintf(bbuf,"\tgoto l%d;\nlabel l%d :\n",$5.dt[2],$5.dt[1]);
	b=ap(strdup(bbuf),$9.code);
	sprintf(bbuf,"label l%d :\n",$5.dt[2]);
	$$.code=ap3(a,b,strdup(bbuf));
	a=ap3(strdup("if("),$3.ast,strdup(")"));
	a=ap3(a,$7.ast,strdup(" else "));
	$$.ast=ap(a,$9.ast);
};


%%