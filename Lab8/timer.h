#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int Timer_init(int num);
int Timer_finalize(void);
int Timer_on(int id);
int Timer_off(int id);
int Timer_print(void);
double Timer_getTime(int id);

struct timeval sTime, eTime, resultTime;
int size;
double *result;
int isInit = 0;


int Timer_init(int num){
	result = malloc(sizeof(double)*num);
	size = num;
	for(int i = 0; i<num; i++){
		result[i] = 0.0;
	}
	isInit = 1;
	return 0;
}

int Timer_finalize(void){
	free(result);
	return 0;
}

int Timer_on(int id){
	if(isInit == 0) {printf("no init\n"); exit(1);}
	gettimeofday(&sTime,NULL);
	return 0;
}

int Timer_off(int id){
	if(isInit == 0) {printf("no init"); exit(1);}
	gettimeofday(&eTime,NULL);
	timersub(&eTime, &sTime, &resultTime);
	result[id] += resultTime.tv_sec*1000 + (double)resultTime.tv_usec/1000;
	return 0;
}

int Timer_print(void){
	if(isInit == 0) {printf("no init"); exit(1);}
	for(int i = 0; i<size; i++){
		printf("Timer %d: %.2lf ms\n", i, result[i]);
	}
	return 0;
}
double Timer_getTime(int id){
	if(isInit == 0) {printf("no init"); exit(1);}
	return result[id];
}
