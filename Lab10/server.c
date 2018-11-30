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
	data dt;
	if((rfd=open("./a",O_RDONLY))==-1){perror("open");exit(0);}
	while(1){
		if((read(rfd,&dt,sizeof(struct data)))==-1){
			perror("read");exit(1);
		}
//		printf("%d %c %d\n",dt.a,dt.c,dt.b);
		switch(dt.c){
		case '+':
			result = dt.a + dt.b;
			flag = 1;
			break;
        case '-':
            result = dt.a - dt.b;
            flag = 1;
            break;
        case '*':
            result = dt.a * dt.b;
            flag = 1;
            break;
        case '/':
            result = dt.a / dt.b;
            flag = 1;
            break;
		}
//		printf("result : %d \n",result);
		if(flag == 1) {
			close(rfd);
			break;
		}
	}
	if((wfd = open("./b",O_WRONLY))==-1){perror("open");exit(1);}
	if((write(wfd,&result,sizeof(int)))==-1){perror("write");exit(1);}	
	close(wfd);
	return 0;
}
