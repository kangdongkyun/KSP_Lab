#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
unsigned int n;
int isMenuOpened=0;
//sigset_t new;

void sigint_handler(int signo);
void sigalrm_handler(int signo);
int menu();

int main(int argc, char* argv[]){
 	signal(SIGINT,sigint_handler);
	signal(SIGALRM,sigalrm_handler);
	n = strtoul(*(argv+1),NULL,10);
//	sigemptyset(&new);
//	sigaddset(&new,SIGINT);
//	sigaddset(&new,SIGALRM);
//	sigprocmask(SIG_UNBLOCK,&new,(sigset_t *)NULL);
	for(;;){
		alarm(n);
		pause();
		
	}
	return 0;

}
void sigalrm_handler(int signo){
//	psignal(signo,"beep!");
	
	if(isMenuOpened == 0){
		isMenuOpened=0;	
	}
	if(isMenuOpened == 0) {
		alarm(n);
		psignal(signo,"beep!");
	}

	
}
void sigint_handler(int signo){
	psignal(signo,"signal");
	isMenuOpened = 1;
	isMenuOpened = menu();
}
int menu(){
	int sel;
	int sec;
	printf("Input the menu number [1. Snooze 2. Set Time 3. End]:");
	scanf("%d", &sel);
	switch(sel){
	case 1:
		printf("Timer Start...\n");
	break;
	case 2:
		printf("Input the time(sec): ");
		scanf("%d",&sec);		
		n=sec;
	break;
	case 3:
		printf("Timer Off\n");
		kill(0,SIGKILL);
	break;
	}
	return 0;	
}
