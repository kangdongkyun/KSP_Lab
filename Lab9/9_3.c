#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
sigset_t new;
int flag,t;
void printHandler(int signo){
	printf("Received Signal : %s\n",strsignal(signo));;
}
void blockHandler(int signo){
	if(flag == 0){
		printf("Do Not Disturb mode on!\n");
//		sigprocmask(SIG_BLOCK, &new, (sigset_t *)NULL);
		flag = 1;
	}
	else {
//		sigprocmask(SIG_UNBLOCK, &new, (sigset_t *)NULL);
		printf("Do Not Disturb mode off!\n");
		printf("[During the DND mode]\n");
		flag = 0;
	}
}
void setSignal(int f){
	if(f == 0){
		for(int i=1;i<=64;i++){
			if(i==SIGKILL||i==SIGSTOP || i== SIGUSR1){}
			else {
				if(signal(i,printHandler)==SIG_ERR) continue;
			}
		}
	}
	else if(f==1){
		for(int i=1;i<=64;i++){
			if(i==SIGKILL||SIGSTOP||i==SIGUSR1){}
			else{
				if(signal(i,SIG_DFL)==SIG_ERR){
					continue;
				}
			}
		}
	}
}
int main(){
	flag = 0;
	t=0;
	sigemptyset(&new);

	if(signal(SIGUSR1, blockHandler) == SIG_ERR){
		perror("error");
		exit(1);
	}
	sigfillset(&new);
	sigdelset(&new,SIGUSR1);

	while(1){
		if(flag==1&&t==1){
			sigprocmask(SIG_BLOCK,&new,(sigset_t*)NULL);
			t=0;
			
		}
		else if(flag == 0&&t == 0){
			setSignal(0);
			sigprocmask(SIG_UNBLOCK, &new, (sigset_t*) NULL);
			t=1;	
		}
		else{
			setSignal(1);
		}
	}	
	return 0;
}
