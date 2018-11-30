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
	int rfd,wfd;
	int flag;
	int result;
	pid_t pid;
	int status;
	data dt;
	if((rfd=open("./a",O_RDONLY))==-1){perror("open");exit(0);}
//	if((rfd = open("./WrPipe",O_RDONLY))==-1){perror("open");exit(0);}
//	if((wfd = open("./RdPipe",O_WRONLY))==-1){perror("open");exit(0);}
//	switch(pid=fork()){
//	case -1: perror("fork");exit(1);break;
//	case 0: //read
//		if((rfd = open("./WrPipe",O_RDONLY))==-1){perror("open");exit(0);}
//		while(1){
//			if((read(rfd,&flag,sizeof(int))<0)){perror("flag");exit(1);}
//			if(!flag) continue;
//			if((read(rfd,&dt,sizeof(struct data)))==-1){perror("read");exit(1);}
//			printf("%d %c %d\n",dt.a,dt.c,dt.b);
//			switch(dt.c){
//			case '+':
//				result = dt.a + dt.b;
//				break;
//			}
//			flag = 0;
//		}
//		break;
//	default :
//		if((wfd = open("./RdPipe",O_WRONLY))==-1){perror("open");exit(1);}
//		wait(&status);
//		if((write(wfd,&result,sizeof(int)))==-1){perror("result");exit(1);}
//		break;
//	}
	while(1){
//		if((read(rfd,&flag,sizeof(int))<0)){
//			perror("flag");exit(1);
//		}
//		if(!flag) continue;
		if((read(rfd,&dt,sizeof(struct data)))==-1){
			perror("read");exit(1);
		}
		printf("%d %c %d\n",dt.a,dt.c,dt.b);
		switch(dt.c){
		case '+':
			result = dt.a + dt.b;
			flag = 1;
			break;
		}
		printf("result : %d \n",result);
		if(flag == 1) break;
//		if((write(wfd,&result,sizeof(int)))==-1){
//			perror("result");exit(1);
//		}
	}
	close(wfd);
	close(rfd);
	return 0;
}
