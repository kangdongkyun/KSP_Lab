#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	char** new_argv;
	
	new_argv = (char**) malloc(sizeof(char*)*(argc+1));
	new_argv[0] = "7_1.out";
	new_argv[1] = argv[1];
	if(execv("/home/kang/Lab7/7_1.out",new_argv)==-1){
		perror("ERROR");
	}
	
	return 0;
}
