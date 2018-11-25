#include <sys/mman.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

int main(int argc,char *argv[]) {
	int fd;
	char* addr;
	char fileName[255] = "map.dat";
	int answer;
	if(argc>1) strcpy(fileName,argv[1]);

	if((fd = open(fileName, O_RDWR)) == -1) {perror("open"); exit(1); }

	addr=  mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);

	int num;
	close(fd);
	while(1){
//		msync(addr,getpagesize(),MS_SYNC);
		if(addr[4] ==  1) {
			printf("게임 끝\n");
			exit(1);
		}
		for(int i=0;i<3;i++){
			scanf("%d",&addr[i]);
			
		}
		addr[3] =1;
		printf("ok\n");
	
	}
}
