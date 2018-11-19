#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <string.h>
int main(int argc, char* argv[]){
	struct group *grp;
	int count=0,n=0,m=0,k;
	char* Buf[100];
	int length;
	while((grp = getgrent())){
		length = strlen(grp->gr_name);
		char *userId = (char*)malloc(sizeof(char)*length);
		Buf[n] = (char*)malloc(sizeof(char)*length);
		userId = grp->gr_name;
		strcpy(Buf[n],userId);
		n++;
	}
	k=n;
	while(k--){
		printf("%s : %s ",Buf[m],Buf[m]);
		setgrent();
		while((grp = getgrent())){
			while(grp->gr_mem[count]!=NULL){
				if(!strcmp(Buf[m],grp->gr_mem[count])){
					printf("%s ",grp->gr_name);
				}
				count++;
			}
			count =0;

		}printf("\n");
		m++;
	}
}
