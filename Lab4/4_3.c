#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#define PRINT_ERR_EXIT(_msg) { perror(_msg); exit(1); }
// 배열 초기화
void clear(char* str, int size)
{	for(int i = 0; i < size; i++)
		str[i] = '\0';
}
// 문자열 숫자를 인트형 숫자로
int makeNum(char* argv2) {
        int n = 0;
        for(int i = 0; argv2[i] != '\0'; i++){
                if('0' > argv2[i] && argv2[i] > '9') {
                        printf("Sampling step size Error");
                        break;
                }
                n = n * 10 + argv2[i] - '0';
        }
        return n;
}
// 첫번째 입력받은 문자열 분리하여 경로만 반환
void getPath(char* argv1, char* path1){
	int i = strlen(argv1);
		while(argv1[i-1] != '/') {
		i--;
	}
		strncpy(path1, argv1,i);
}
// 첫번째 입력받은 문자열 분리하여 prefix만 반환
void getPrefix(char* argv1, char* prefix){
		int i = strlen(argv1);
	int k = i;
	int n = 0;
		while(argv1[i-1] != '/') {
                i--;
        }
	for(int j = i; j < k; j++) {
                prefix[n] = argv1[j];
		n++;
	}
	}
// 파일의 이름과 prefix 가 일치하는 지 확인
int matched(char* a, char* b){
		for(int i = 0; i < strlen(b); i++) {
		if(a[i] != b[i])
			return 0;
	}
	return 1;
}
// prefix 만들기
void makePrefix(int n, char* prefixNum){
	int i = 2;
	while (i >= 0) {
		prefixNum[i] = n % 10+ '0';
		n = n / 10; 
		i--;
	}
	prefixNum[3] = '\0';
}int main(int argc, char *argv[]) {
	DIR *dp;
	struct dirent *dent;
	char prefix[100];
	char path1[100];
	char path2[100];
	char path3[100];
	char prefixNum[4];
	int checking = 0;
	int step = makeNum(argv[2]);
	int count = step;
	int i = 1;
		clear(prefix, 100);
	clear(path1, 100);
	clear(path2, 100);
	clear(path3, 100);	
	getPrefix(argv[1], prefix);
        getPath(argv[1], path1);
	getPath(argv[1], path2);
	getPath(argv[1], path3);
	chdir(path1);
	if((dp = opendir(".")) == NULL) {
		perror("opendir");
		exit(1);
	}
		mkdir(argv[3], 0755);
		
	while((dent = readdir(dp))) {
		if((checking = matched(dent->d_name, prefix))==1) {
			if(count == step) {
				strcat(path1,dent->d_name);
				strcat(path2,argv[3]);
				makePrefix(i,prefixNum);
				strcat(path2,"/");
				strcat(path2,prefix);
				strcat(path2,prefixNum);
				printf("target : %s  linkfile : %s \n", path1, path2);
				symlink(path1,path2);
				strcpy(path1,path3);
				strcpy(path2,path3);
				count = 0;
				i++;
			}
			count++;
		}
		printf("name: %s count :  %d  i : %d \n", dent->d_name, count, i);
	}
	closedir(dp);
	return 0;
}
