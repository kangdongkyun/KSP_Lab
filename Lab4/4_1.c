#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PRINT_ERR(_msg) {perror(_msg); exit(1);}
#define BUF_S 100

struct dirent* direntSetPath(char* s1, struct dirent *x){
	char str[256];
	struct dirent *y =(struct dirent*)malloc(sizeof(struct dirent));
	y->d_type = x->d_type;
	strcpy(str,s1);
	strcat(str,"/");
	strcat(str, x->d_name);
	strcpy(y->d_name,str);
	return y;
}
int openReadDir(char *s1,struct dirent *dent[], int start, int count){
	DIR *dp;
	struct dirent *x;
	if((dp = opendir(s1))==NULL)PRINT_ERR("opendir");
	while(x = readdir(dp)){
		if(x->d_name[0] == '.')continue;
		x = direntSetPath(s1,x);
		dent[(start+count)%BUF_S] = x;
		count++;
	}
	closedir(dp);
	return count;
}
int main(int argc,char*argv[]){
	struct dirent *dent[BUF_S];
	int count =0,start = 0,exist=0;
	struct dirent *x;
	char str[256]= "./";
	char target[256] = "/";
	strcat(str,argv[1]);
	strcat(target,argv[2]);
	count = openReadDir(str, dent , start, count);
	while(count!=0){
		x= dent[start];
		count--;
		start=(start+1)%BUF_S;
		if(strstr(x->d_name,target)){
			printf("%s\n",x->d_name);
			exist =1;
		}
		else if((int)x->d_type==4){
			count = openReadDir(x->d_name,dent,start, count);
		}
		free(x);

	}
	if(exist = 0) printf("NOT file\n");
	return 0;
}
