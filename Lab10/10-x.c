#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
char buf[256]="\0";
typedef struct data_t{
int a;
int b;
char c;
}data_t; 
int main(int argc, char* argv[]){
	int pd1, pd2, n;
	data_t data;	
	mkfifo(argv[1],0666);
	mkfifo(argv[2],0666);
	pid_t pid;
//	if((pd1 = open(argv[1],O_WRONLY))==-1){perror("error");exit(1);}
//	if((pd2 = open(argv[2],O_RDONLY))==-1){perror("error");exit(1);}
	
	switch(pid=fork()){
	case -1:
		perror("fork"); exit(1); break;
	case 0 : // child process : read
		if((pd2=open(argv[2],O_RDONLY))==-1){perror("open");exit(1);}
//		close(pd1);
		while(1){
		//	read(pd2,buf,256);
		//	printf("[%s] : %s\n",argv[2],buf);
			read(pd2,&data,sizeof(struct data_t));
			int result = data.a + data.b;
			printf("%d",result);				
		}
		break;
	default : // parent process : write
		if((pd1=open(argv[1],O_WRONLY))==-1){perror("open");exit(1);}
//		close(pd2);
		while(1){
			
//			scanf("%s",buf);
			scanf("%d",&data.a);
			scanf("%c",&data.c);
			scanf("%d",&data.b);

//			int n = strlen(buf);
//			if(write(pd1, buf, n)==-1){
//				perror("write");exit(0);
//			}
			if(write(pd1, &data, sizeof(struct data_t))==-1){ 
				perror("write");
				exit(0);
			}
		}
		break;	
	}	
	close(pd1);
	close(pd2);
	return 0;
}
