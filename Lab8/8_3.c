#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "Timer.h"

FILE* fp;
int* primeArray;

void Serial(unsigned int start, unsigned int end);
void Parallel(unsigned int start, unsigned int end,int procNum);
int isPrimeNumber(int n);
int findPrimeNumer(int start,int end);
void printFile(int count);
int main(int argc, char* argv[]){
	unsigned int start = strtoul(argv[1],NULL,10); // 처음 소수 판별할 수 형변환
	unsigned int end = strtoul(argv[2],NULL,10); // 마지막 소수 판별할 수 형변환 
	unsigned int processnum = strtoul(argv[3],NULL,10); //프로세스 개수 형변환
	fp = fopen(argv[4],"w"); // 소수 printf할 파일 open
	
	if(processnum==1){
		Serial(start,end); // 단일 프로세스일때
	}
	else if(processnum>1){
		Parallel(start,end,processnum); // 다중 프로세스일때
	}
}
void Serial(unsigned int start, unsigned int end){
	int count = 0;
	myTimer_init(1); // 타이머 초기화
	myTimer_on(0); // 0번 타이머 시작
	count=findPrimeNumber(start,end); // 소수를 찾아 찾은 소수의 갯수를 count에 저장
	myTimer_off(0); // 0번 타이머 종료
	printf("[Serial] takes ");
	myTimer_print();
	myTimer_finalize(); // 타이머 free
	printFile(count); // FILE에 소수 출력
}
void Parallel(unsigned int start, unsigned int end,int procNum){
	pid_t pid;
	int status,proc,count =0;
	int divide = (end - start +1)/procNum; // 적당히 일을 나누기 위한 변수
	myTimer_init(1); // 타이머 초기화
	myTimer_on(0); // 0번 타이머 시작
	for(int i=1;i<=procNum-1;i++){ // 프로세스 갯수를 입력받은만큼 반복
		switch(pid = fork()){// fork()함수 실행해서 pid에 저장
		case -1: // fork가 에러난 경우
			perror("fork");
			exit(1);
			break;
		case 0:
			proc = i; // i를 proc에 저장
			break;
		default: 
			break;	
		}
		if(pid>0)break;	//pid가 0이 아니면 종료
	}
	if(proc == 0){ //proc == 0 이면(부모 프로세스이면)
		count = findPrimeNumber(start+divide*(procNum-1),end); // 가장 마지막 구간 소수 찾기
	}
	else{ // 자식프로세스들은
		count = findPrimeNumber(start + divide *(procNum - proc - 1),start + divide*(procNum-proc)-1); // 생성생 순서대로 앞에서부터 소수 찾기
	}
	if(proc!=procNum -1){
		while(wait(&status) != pid) continue; //자식프로세스가 모드 끝날때까지 부모프로세스 종료하지않고 대기
	}
	myTimer_off(0); //0번 타이머 종료
	if(proc == 0){ // 부모 프로세스일 경우 아래 출력
		printf("[Parallel] takes ");
		myTimer_print();
	}
	printFile(count); // 찾은 소수를 FILE에다가 출력
}
int isPrimeNumber(int n){ // 소수가 맞으면 1 아니면 0을 반환
	int i=0;
	for(i=2;i<n/2;i++)
		if((n%i)==0) return 0;
	return 1;
}
int findPrimeNumber(int start, int end){
	int count=0;// 소수의 갯수를 저장할 변수
	primeArray = (int*)malloc(sizeof(int)*(end-start+1));//찾아야할 모든 수만큼 동적할당
	for(int i=start;i<=end;i++){
		if(isPrimeNumber(i)==1){// i가 소수면
			primeArray[count]=i; // primeArray에 i저장
			count++;// 소수갯수 1 증가
		}
	}
	printf("[P%d] found %d primes\n",(int)getpid(),count);
	return count;
}
void printFile(int count){
	for(int i=0;i<count;i++){
		fprintf(fp,"%d ",primeArray[i]); //file에 찾은 소수 쓰기
	}
	fprintf(fp,"\n");
}