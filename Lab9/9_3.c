#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int flag, t;
sigset_t set;

void printSig(int sig){
	printf("Received Signal : %s\n", strsignal(sig));
}
void blockSignal(int signo){
	if(flag == 0){
		printf("Do Not Disturb mode on!\n");
		flag = 1;
		t = 1;
	}
	else{
		printf("Do Not Disturb mode off!\n");
		flag = 0;
		t = 0;
		printf("[During the DND mode]\n");
	}
}

void setSignal(int f){
	if(f == 0){
		for(int i= 1; i<=64; i++){
			if(i == SIGKILL || i == SIGSTOP || i == SIGUSR1){}
			else{
				if(signal(i, printSig) == SIG_ERR){
					continue;
				}
			}
		}
	}
	else if(f == 1){
		for(int i= 1; i<=64; i++){
			if(i == SIGKILL || i == SIGSTOP || i == SIGUSR1){}
			else{
				if(signal(i, SIG_DFL) == SIG_ERR){
					continue;
				}
			}				
		}
	}
}


int main(void){
	flag = 0;
	t = 0;

	if(signal(SIGUSR1, blockSignal) == SIG_ERR){
		fprintf(stderr, "Cannot Handle SIGUSR1");
		exit(EXIT_FAILURE);
	}
	sigfillset(&set);
	sigdelset(&set, SIGUSR1);

	while(1){
		if(flag == 1 && t == 1){
			sigprocmask(SIG_BLOCK, &set, (sigset_t *)NULL);
			t = 0;
		}
		else if(flag == 0 && t == 0){
			setSignal(0);
			sigprocmask(SIG_UNBLOCK, &set, (sigset_t *)NULL);
			t = 1;
		}
		else{
			setSignal(1);
		}
	}

	return 0;
}

