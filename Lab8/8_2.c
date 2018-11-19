#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
	unsigned int n = strtoul(*(argv+1),NULL,10);
	pid_t pid;
	pid_t *pids = (pid_t*)malloc(sizeof(pid_t)*n);
	int processnum = 0;
	int sum,status;
	printf("You typed number : %d\n",n);
	while(processnum < n){
		switch(*(pids+processnum) = fork()){
		case -1 : 
			perror("fork");
			exit(0);
			break;
		case 0 :
			printf("Child Process PID : %d, MyParent's PID : %d\n",(int)getpid(),(int)getppid());//*(pids+processnum));
			sleep(1);
			exit(processnum+1);
			break;
		default :
			while(wait(&status) == pids[processnum]){
				sum+=WEXITSTATUS(status);
				
			}	
				
		//	printf("[Arithmetic Series]\n");
		//	sum += WEXITSTATUS(status);
		//	printf("a = 0, d = 1, n = %d, Result = %d\n",n,sum);
			break;
		}
		processnum++;
		if(processnum==n){
			printf("[Arithmetic Series]\n");
			printf("a = 0, d = 1, n = %d, Result = %d\n",n,sum);
		}
	}
	return 0;
}
