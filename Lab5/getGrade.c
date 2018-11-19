#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
struct info{
char* id;
char* grade;
};
int main(int argc, char* argv[]){
	FILE *rfp, *wfp;
	struct info stu[5];
	uid_t uid, euid,suid;
	uid = getuid();
	euid = geteuid();
	
	printf("%d , %d\n",uid, euid);
	if((rfp = fopen(argv[2],"r"))==NULL){
		perror("ERROR");
		exit(1);
	}
	if((wfp = fopen("myGrade.txt","w"))==NULL){
		perror("ERROR");
		exit(1);
	}
	for(int i=0;i<5;i++){
		stu[i].id = (char*) malloc(sizeof(char)*9);
		stu[i].grade = (char*) malloc(sizeof(char)*3);
		fscanf(rfp,"%s %s",stu[i].id,stu[i].grade);
		if(!strcmp(argv[1],stu[i].id)){
			printf("My Grade is %s\n",stu[i].grade);
			euid = getuid();
			printf("%d ,%d\n",uid, euid);
			fprintf(wfp,"id : %s, My Grade is %s",stu[i].id,stu[i].grade);
			break;
		}
	}	
	fclose(rfp);
	fclose(wfp);
	return 0;
}

