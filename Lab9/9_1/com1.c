#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define _RANDOM 100

#define CHECK_MMAP_SUCCESS(_UpDownGame)\
if(_UpDownGame == MAP_FAILED) { perror("mmap"); exit(1); }

int main(int argc, char* argv[]){
	srand(time(NULL));
	int fd;
	caddr_t addr;
	char fileName[255] = "answer.txt";
	int div = 100 ,add = 1,answer,key; 
    	if (argc > 1) strcpy(fileName, argv[1]);    
	if ((fd = open(fileName, O_RDWR)) == -1) { perror("open"); exit(1); }

	addr = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
	
	msync(addr,getpagesize(),MS_SYNC);
	close(fd);
	key = addr[3];
	addr[0] = 1; //turn
	addr[5] = 0; // win
	answer = rand()%div + 1;
	while(answer != key){
        	if(addr[0]==1){
	            	printf("com1 : %d ", answer);
        	    	if(answer > key){
                		printf("Down!\n");
		                if(div >= answer){
                			div =  answer - 1; 
		                }
	       		}	
		        else if(answer < key){
			        printf("Up \n");
				if(add < answer){
					add = answer;
        		        }
			}
			sleep(1);
		        addr[0]=2;
			answer = rand()%(div - add) + (add + 1);
			if(addr[5]==2) exit(1);
        	}
	}
	printf("%d Great!\n", answer);
	addr[5] = 1;
}
