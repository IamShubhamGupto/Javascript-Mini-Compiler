#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
			strcpy(arg1[--lineno], strdup("NULL"));
			strcpy(arg2[--lineno], strdup("NULL"));
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
		fprintf(f2,"%s\t\t%s\t\t%s\t\t%s\n",op[i],arg1[i],arg2[i],res[i]);
    }
	fclose(f);
	fclose(f2);
}

int main(){
    generate_quads();
    return 0;
}