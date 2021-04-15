#ifndef HEADER_H
#define HEADER_H
#define DEBUG 0
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

// void generate_quads(const char* tac_code){

// 	char ignore[] = {'\t', ' ', '\n', ';', ':'};
// 	char* op;
// 	char* arg1;
// 	char* arg2;
// 	char* res;
// 	int lines = 0;

// 	int len = strlen(tac_code);
// 	if(DEBUG){
// 		printf("Length of code = %d\n",len);
// 	}
	
// 	int i = 0;
// 	int j = 0;
// 	int first = 0;
// 	int last = 0;
// 	int flag = 0;
// 	for(i = 0; i < len; ++i){
// 		first = i;
// 		flag = 0;
// 		for(j = 0; < 5; ++j){
// 			if(tac_code[i] == ignore[j]){
// 				flag = 1;
// 				break;
// 			}
// 		}
// 		if(!flag){

// 		}
// 	}
// 	// while(i < len){
// 	// 	if(tac_code[i] == '\n'){
// 	// 		++lines;
// 	// 	}
// 	// 	++i;
// 	// }
// 	// char*** quadruple = (char***)malloc(sizeof(char**)*lines);
// 	// for(i = 0; i < lines; i++){
// 	// 	quadruple[i] = (char**)malloc(sizeof(char**)*4);
// 	// 	for(j = 0; j < 4; ++j){
// 	// 		quadruple[i][j] = (char*)malloc(sizeof(char)*8);
// 	// 	}
// 	// }
// }
#endif