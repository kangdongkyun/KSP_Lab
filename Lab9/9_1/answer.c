#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define CHECK_MMAP_SUCCESS(_UpDownGame)\
if(_UpDownGame == MAP_FAILED) { perror("mmap"); exit(1); }

#define _RANDOM 100

int main(int argc, char* argv[]) {    
	srand(time(NULL));
	int fd;
	char fileName[255] = "answer.txt";
	caddr_t addr;
	if (argc > 1) strcpy(fileName, argv[1]);
	if ((fd = open(fileName, O_RDWR)) == -1) { perror("open"); exit(1); }

	addr = mmap(0, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
	CHECK_MMAP_SUCCESS(addr);
	close(fd);
   
	addr[3] = rand() % _RANDOM + 1; // com1 
	addr[4] = rand() % _RANDOM + 1; // com2
	

	printf("com1 answer : %d\n", addr[3]); 
	printf("com2 answer : %d\n", addr[4]);  

	return 0;
}

