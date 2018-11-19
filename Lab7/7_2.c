#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "Timer.h"
#include <math.h>
double fibo(double n){
	return (pow((1+sqrt(5)),n)-pow((1-sqrt(5)),n))/(pow(2,n)*sqrt(5));
}
int main(int argc, char* argv[]){
	pid_t pid;
	register int n=0;
	unsigned int fr = strtoul(*(argv+1),NULL,10);
	register double num = strtof(*(argv+2),NULL);
	printf("PID	PPID	Child	Running time\n");
	while(n<(int)fr){
		pid = fork();
		n++;
	}		
	myTimer_init(1);
	myTimer_on(0);
	fibo(num);
	myTimer_off(0);
	printf("%d	%d	%d	",(int)getpid(),(int)getppid(),(int)pid);
	myTimer_print();	
	return 0;
}
