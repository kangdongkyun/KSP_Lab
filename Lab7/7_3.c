#include "Timer.h"
#include <unistd.h>
#include <string.h>
#include <math.h>
int Prime(int a,int b){
	int i, n, j, flag, count= 0;
//	for(int n=a;n<=b;n++){
//		for(i=a+1;i<n;i++){
//			if(n%i==0) break;
//		}
//		if(i==n) {
//			count++;
//			printf("%d\n",i);
//		}
//	}
	for( i = a; i<=b;i++){
		flag = 1;
		n = (int)sqrt(i);
		for(j=2;j<=n;j++){
			if(i%j==0){
				flag=0;
				break;
			}
		}
		if(flag==1) {
			count++;		
		}
	}
	return count;
}
void Serial(int a,int b){
	int count = 0;
	printf("[Serial start]\n");
	myTimer_init(1);
	myTimer_on(0);
	int num = Prime(a,b);
	myTimer_off(0);
	printf("[Serial] found %d primes\n", num);
	printf("[Serial end] \n");
	printf("[Serial running Time] : ");
	myTimer_print();
	myTimer_finalize();
}
void Parallel(int a,int b){
	int mid = (a+b)/2+1;
	int count;
	pid_t pid;
	printf("[Parallel start]\n");
	
	switch(pid = fork()){
	case -1:
		perror("fork");
		exit(1);
	break;

	case 0:
		myTimer_init(1);
		myTimer_on(0);
		count = Prime(a,mid);
		myTimer_off(0);
		printf("[pid = %d] I found %d prime numbers betweenn(%d ~ %d)\n" , getpid(),count,a,mid);
		printf("[pid = %d] takes ",getpid());
		myTimer_print();
		myTimer_finalize();
		printf("[Proc.%d end]\n",getpid());
		
	break;

	default:
		myTimer_init(1);
		myTimer_on(0);
		count = Prime(mid,b);
		myTimer_off(0);
		printf("[pid = %d] I found %d prime numbers between(%d ~ %d)\n",getpid(),count,mid,b);
		printf("[pid = %d] takes ",getpid());
		myTimer_print();
		myTimer_finalize();
		printf("[Proc.%d end]\n",getpid());	
	break;
	}
	
}

int main(int argc,char* argv[]){
	unsigned int a, b;
	pid_t pid;
	a=strtoul(*(argv+1),NULL,10);
	b=strtoul(*(argv+2),NULL,10);
	Serial(a,b);	
	Parallel(a,b);  
	return 0;
}
