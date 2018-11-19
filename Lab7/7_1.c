#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	char* arg = strtok(argv[1],"=");
	int count = 0;char* name;char* value;
	FILE* fp;
	fp=fopen("/home/kang/.bashrc","a+");
	while(arg != NULL && count < 2){
//		printf("%s\n", arg);
		if(count==0) name = arg;
		else if(count==1) value = arg;
		else break;
		arg = strtok(NULL,"=");
		count++;
	}
//	printf("%s=%s\n",name,value);
	if((setenv(name,value,1))!=0){
		perror("ERROR");
	}
//	printf("%s",getenv(name));	
	fprintf(fp,"export %s=%s\n",name,value);
	fclose(fp);
	return 0;
}
