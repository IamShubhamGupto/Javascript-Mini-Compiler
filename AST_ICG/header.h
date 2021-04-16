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
    char* line = NULL;
    size_t lent = 0;
    char op[100][100];
	char arg1[100][100];
	char arg2[100][100];
	char res[100][100];
    int len;
	int lineno = 0;
    char* tokens;
    char* t_count;
    int i;
    while(getline(&line, &lent, f) != -1) {
        char line_copy[100];
        strcpy(line_copy,line);
        t_count = strtok(line_copy," ");
        len = 0;

        //count number of tokens
        while(t_count != NULL){
            ++len;
            //printf("processing token %s\n",tokens);
            t_count = strtok(NULL, " ");
        }
        tokens = strtok(line," ");
        i = 0;
        while(tokens != NULL){
            //printf("processing token %s, length %d\n",tokens, len);
            if(tokens[strlen(tokens)-1] == '\n'){
                tokens[strlen(tokens)-1] = '\0';
            }
			if(len == 2){
				if(i == 0){
					strcpy(op[lineno], strdup(tokens));
				}else if(i == 1){
					strcpy(res[lineno], strdup(tokens));
				}	
			}else if(len == 3){
                //printf("lineno %d length = 3\n",lineno);
				if(i == 0){
					strcpy(res[lineno], strdup(tokens));
				}else if(i == 1){
					strcpy(op[lineno], strdup(tokens));
				}else if(i == 2){
					strcpy(arg1[lineno], strdup(tokens));
				}

			}else if(len == 4){
				if(i == 0){
					strcpy(op[lineno], strdup(tokens));
				}else if(i == 1){
					strcpy(arg1[lineno], strdup(tokens));
				}else if(i == 3){
					strcpy(res[lineno], strdup(tokens));
				}

			}else if(len == 5){
				if(i == 0){
					strcpy(res[lineno], strdup(tokens));
				}else if(i == 2){
					strcpy(arg1[lineno], strdup(tokens));
				}else if(i == 3){
					strcpy(op[lineno], strdup(tokens));
				}else if(i == 4){
					strcpy(arg2[lineno], strdup(tokens));
				}
			}	
			++i;
			tokens = strtok(NULL," ");
		}
        if(len == 2){
			strcpy(arg1[lineno], strdup("NULL"));
			strcpy(arg2[lineno], strdup("NULL"));
		}else if(len == 3 || len == 4){
			strcpy(arg2[lineno], strdup("NULL"));
		}
        ++lineno;
        // printf(" line = %s|||line length: %zd\n",line, strlen(line));
    }
    printf("\n\nQuadruples\n\n");
	printf("op\t\targ1\t\targ2\t\tres\n");
    for(i = 0; i < lineno; ++i){
        printf("%s\t\t%s\t\t%s\t\t%s\n",op[i],arg1[i],arg2[i],res[i]);
		fprintf(f2,"%s %s %s %s\n",op[i],arg1[i],arg2[i],res[i]);
    }
	fclose(f);
	fclose(f2);
}
#endif