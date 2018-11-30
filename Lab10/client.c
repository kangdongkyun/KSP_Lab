#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
typedef struct data{
	int a;
	int b;
	char c;
}data;

int main(int argc, char* argv[]){
	int rfd,wfd,status;
	data dt;
	int result,flag=0;
	pid_t pid;	
	if((wfd = open("./a",O_WRONLY))==-1){perror("error");exit(0);}
	printf("Please enter formula (ex: 1 + 2) : ");
	scanf("%d ",&dt.a);
	scanf("%c ",&dt.c);
	scanf("%d",&dt.b);
//	printf("%d %c %d\n",dt.a,dt.c,dt.b);
	if(write(wfd,&dt,sizeof(struct data))==-1){
		perror("data write");
		exit(0);
	}
	sleep(1);
	close(wfd);
	if((rfd = open("./b",O_RDONLY))==-1){perror("open");exit(1);}
	if(read(rfd,&result,sizeof(int))==-1){
		perror("read error");
		exit(0);
	}
	printf("result : %d\n", result);
	close(rfd);
	return 0;
}
