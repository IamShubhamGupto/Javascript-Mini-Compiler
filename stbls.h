struct tentr{
	int type,scope,lndec,lnused;
	struct tentr *n;
	char *d;
};

struct tentr idtopp={0},stopp={0},ntopp={0};

void mkentr(int type,char *d,int scp){
	struct tentr *a,*b;
	switch(type){
	case 0:a=&idtopp;break;
	case 1:a=&stopp;break;
	case 2:a=&ntopp;break;
	default:return;
	}
	while(a->n!=NULL){
		if(strcmp(a->n->d,d)==0)return;
		a=a->n;
	}
	b=malloc(sizeof(struct tentr));
	b->n=NULL;
	b->d=strdup(d);
	a->n=b;
	if(type==0){
		b->scope=scp;
		b->lndec=b->lnused=elno;
		b->type=-1;}
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
		printf("%s ",a->n->d);
		a=a->n;
	}
	printf("\n");
}

void chkentr(char *d){
	int tp=stop-1,pscp;
	//printf("chkentr called!!!\n");
	struct tentr *a;
	for(tp=stop-1;tp>=0;tp--){
		pscp=scope[tp];
		a=&idtopp;
		while(a->n!=NULL){
			if(strcmp(d,a->n->d)==0&&pscp==a->n->scope){
				a->n->lnused=elno;
				return;
			}
			a=a->n;
		}
	}
	printf("Error in line %d, %s not found\n", elno,d);
}

void add_type_name(char *d, int type){
	int tp=stop-1,pscp;
	struct tentr *a;
	for(tp=stop-1;tp>=0;tp--){
		pscp=scope[tp];
		a=&idtopp;
		while(a->n!=NULL){
			if(strcmp(d,a->n->d)==0&&pscp==a->n->scope){
				a->n->type=type;
				return;
				}
			a=a->n;
			}
	}
	printf("Error in line %d, %s not found\n", elno,d);
}
