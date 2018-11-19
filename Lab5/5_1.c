#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	struct spwd *spw;
	spw=getspnam("sp11");
	char *pwnam=spw->sp_pwdp;
//	printf("%s\n",pwnam);
	char* buf[3];
	char* ext = strtok(pwnam,"$");
	int i=0;
	while(ext!=NULL){
		int length = strlen(ext);
		buf[i]=(char*)malloc(sizeof(char)*length);
		buf[i] = ext;
		ext = strtok(NULL,"$");
		i++;
	}
	printf("Hashid : %s \nSalt = %s\nHash value : %s\n",buf[0],buf[1],buf[2]);

	int date = spw->sp_lstchg;
	int year,mon,day;
	year = date/365 + 1970;
	int temp = date%365;
	mon = temp / 30+1;
	day = temp%30+1;
	printf("Last Change Date : %d / %d / %d\n",year,mon,day);


	return 0;
}
