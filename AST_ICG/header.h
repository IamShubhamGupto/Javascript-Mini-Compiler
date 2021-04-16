#ifndef HEADER_H
#define HEADER_H
#define DEBUG 1
struct tentr{
	int type;
	int scope;
	int lndec;
	int lnused;
	struct tentr *n;
	char *d;
};

struct tentr idtopp={0};
struct tentr stopp={0};
struct tentr ntopp={0};

int mkentr(int type,char *d,int scp)
{
	struct tentr *a;
	struct tentr *b;
	int c=0;
	switch(type){
		case 0:
			a=&idtopp;
			break;
		case 1:
			a=&stopp;
			break;
		case 2:
			a=&ntopp;
			break;
		default:return -1;
	}
	while(a->n!=NULL){
		if(strcmp(a->n->d,d)==0)
			return c;
		a=a->n;
		c++;
	}
	b=malloc(sizeof(struct tentr));
	b->n=NULL;
	b->d=strdup(d);
	a->n=b;
	if(type==0){
		b->scope=scp;
		b->lndec=b->lnused=elno;
		b->type=-1;
	}
	return c;
}

void printall(){
	struct tentr *a;
	printf("\n\nidentifiers:\n");
	a=&idtopp;
	printf("Name \t scope \t type \t declared line \t last used line\n");
	printf("--------------------------------------------------------\n");
	while(a->n!=NULL){
		printf("%s \t %d \t %d \t %d \t\t %d\n",a->n->d,a->n->scope,a->n->type,a->n->lndec,a->n->lnused);
		a=a->n;
		}
	printf("\n\nstrings:\n");
	a=&stopp;
	while(a->n!=NULL){
		printf("%s\n",a->n->d);
		a=a->n;
		}
	printf("\n\nnumber:\n");
	a=&ntopp;
	while(a->n!=NULL){
		printf("%s\n",a->n->d);
		a=a->n;
	}
}


int chkentr(const char *d)
{
	int tp=stop-1;
	int pscp;
	if(DEBUG)
	{
		printf("chkentr called!!!\n");
	}
	
	struct tentr *a;
	int c=0;
	for(tp=stop-1;tp>=0;tp--)
	{
		pscp=scs[0];a=&idtopp;
		while(a->n!=NULL)
		{
			if(strcmp(d,a->n->d)==0 && (pscp==a->n->scope||1))
			{
				a->n->lnused = elno;
				return c;
			}
			a=a->n;c++;
		}
	}
		
	printf("Error in line %d, %s not found\n", elno,d);
	if(DEBUG)
	{
		printf("chkentr exited\n");
	}
	return -1;
}

void add_type_name(const char *d, int type)
{
	int tp=stop-1,pscp;
	struct tentr *a;
	for(tp=stop-1;tp>=0;tp--){
		pscp=scs[tp];
		a=&idtopp;
		while(a->n!=NULL){
			if(strcmp(d,a->n->d)==0&&pscp==a->n->scope){
				a->n->type=type;return;}a=a->n;
			}
		}
		
	printf("Error in line %d, %s not found\n", elno,d);
}

//more string functions

char* ap(const char *a, const char *b)
{
	int n = strlen(b);
	int m = strlen(a);
	char *o = malloc(sizeof(char)*(m+n+10));
	strcpy(o,a);
	strcpy(o+m,b);
	return o;
}

char* ap3(const char *a, const char *b, const char *c)
{
	int m = strlen(a);
	int n = strlen(b);
	int p = strlen(c);
	char *o = malloc(sizeof(char)*(m+n+p+10));
	strcpy(o,a);
	strcpy(o+m,b);
	strcpy(o+m+n,c);
	return o;
}

char* getname(int c)
{
	struct tentr *t =idtopp.n;
	int i;
	for(i=0; i<c; i++)
		t=t->n;
	return t->d;
}

char* getsname(int s)
{
	return "<sign>";
}

void generate_quads(){
	FILE *f; f=fopen("icg.txt","r");
	FILE *f2 = fopen("quads.txt","w");
	if(f==NULL){
		exit(EXIT_FAILURE);
	}

	fclose(f);
	fclose(f2);
}
#if 0
void generate_quads(char* tac_code){
	char* lines = strtok(tac_code, "\n");
	char* tokens;
	int i;
	int len;	
	char op[100][16];
	char arg1[100][16];
	char arg2[100][16];
	char res[100][16];
	int lineno = 0;
	while(lines != NULL){
		if(DEBUG){
			printf("line = %s\n", lines);
		}
		i = 0;
		
		char* line = strdup(lines);
		len = strlen(line);
		printf("line = %s\n",line);
		tokens = strtok(line," ");
		while(tokens != NULL){
			if(len == 3){
				if(i == 0){
					strcpy(op[lineno], tokens);
				}else if(i == 1){
					strcpy(res[lineno], tokens);
				}	
			}else if(len == 4){
				if(i == 0){
					strcpy(res[lineno], tokens);
				}else if(i == 1){
					strcpy(op[lineno], tokens);
				}else if(i == 2){
					strcpy(arg1[lineno], tokens);
				}
			}else if(len == 5){
				if(i == 0){
					strcpy(op[lineno], tokens);
				}else if(i == 1){
					strcpy(arg1[lineno], tokens);
				}else if(i == 3){
					strcpy(arg1[lineno], tokens);
				}
			}else if(len == 6){
				if(i == 0){
					strcpy(res[lineno], tokens);
				}else if(i == 2){
					strcpy(arg1[lineno], tokens);
				}else if(i == 3){
					strcpy(op[lineno], tokens);
				}else if(i == 4){
					strcpy(res[lineno], tokens);
				}
			}	
			++i;
			tokens = strtok(NULL," ");
		}
		if(len == 3){
			strcpy(arg1[lineno], strdup("NULL"));
			strcpy(arg2[lineno], strdup("NULL"));
		}else if(len == 5 || len == 4){
			strcpy(arg2[lineno], strdup("NULL"));
		}
		lines = strtok(NULL,"\n");
		++lineno;
	}

	for(i = 0; i < lineno; i++){
		printf("%s\t\t%s\t\t%s\t\t%s\n", op[i],arg1[i],arg2[i],res[i]);
	}
}
#endif
#endif