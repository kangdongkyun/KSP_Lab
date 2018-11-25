#include <sys/mman.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

#define CHECK_MMAP_SUCCESS(_addr)\
 if(_addr == MAP_FAILED) { perror("mmap"); exit(1); }

int main(int argc,char* argv[]){
	int fd;
	int answer[3];
	int s=0, b=0;
	caddr_t addr;
	char fileName[255] = "map.dat";

	if(argc>1) strcpy(fileName,argv[1]);
	if((fd = open(fileName, O_RDWR)) == -1) {perror("open"); exit(1); }

	addr = mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    	CHECK_MMAP_SUCCESS(addr);
	addr[4]=0;
	close(fd);
	srand(time(NULL));
	for(int i=0;i<3;i++){
		answer[i] = rand()%9+1;
		for(int j=0;j<i;j++) {
			if(answer[j] == answer[i]){
				i--;
				break;
			}
		}
	}
	printf("answer : ");
	for(int i=0; i< 3; i++) {
		printf("%d ", answer[i]);
	}
	printf("\n");
	while(1){
		if(addr[3] == 1){
			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					if(answer[i] == addr[j] && i == j) s++;
					if(answer[i] == addr[j] && i != j) b++;
				}
			}
			if( s==3 ){
				addr[4] = 1;
				printf("%d %d %d \t 정답!\n",addr[0],addr[1],addr[2]);
				break;
			}
			printf("%d %d %d \t [%d strike, %d ball] \n",addr[0],addr[1],addr[2],s,b);
			s=0;
			b=0;
			addr[3] = 0;
		}
	}
	return 0;
}
