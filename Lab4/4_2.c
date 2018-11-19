#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
char* initStr(){
	char *a='\0';
	return a;

}
int main(int argc, char* argv[]){
	DIR *dp;
	struct dirent *dent;
	char path[BUFSIZ];
	struct stat buf;
	printf("Find %s in %s\n",argv[2],argv[1]);
	if((dp = opendir(argv[1]))==NULL){
		perror("error");
		exit(1);
	}
	while((dent = readdir(dp))){
		strcat(path,"./");
		strcat(path,argv[1]);
		strcat(path,"/");
		strcat(path,dent->d_name);
//		strcat(path,"/");
//		printf("%s\n",path);

		lstat(path,&buf);
		char ch = argv[2][0];
//		if(ch=='I')lstat(path,&buf);
//		else stat(path,&buf);
//		printf("%c\n",ch);
		switch(ch){
		case 'F':
			if(S_ISFIFO(buf.st_mode)) printf("%s\n",path);
			break;
		case 'R':
			if(S_ISREG(buf.st_mode)) printf("%s\n",path);
			break;
		case 'I':
			if(S_ISLNK(buf.st_mode)) printf("%s\n",path);
			break;
		case 'D':
			if(S_ISDIR(buf.st_mode)) printf("%s\n",path);
			break;
		case 'B':
			if(S_ISBLK(buf.st_mode)) printf("%s\n",path);
			break;

		}
		*path = initStr();
	}
	return 0;
}
