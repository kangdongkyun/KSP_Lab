#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main(int argc, char* argv[]) {
	int rfd, wfd, n;
	unsigned int chunkSize;
	clock_t start, end;

	chunkSize = strtoul(*(argv+1),NULL,10);
	printf("%d\n", chunkSize);

	char* buf = (char*) malloc(sizeof(chunkSize));
	srand((unsigned int)time(NULL));

	start = time(NULL);
	rfd = open("gradle.zip", O_RDONLY);
	if(rfd == -1){
		perror("RfdopenError\n");
		exit(1);
	}

	wfd = open("gradle(1).zip", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(wfd == -1){
		perror("WfdOpen Error\n");
		exit(1);
	}
	while(n = read(rfd, buf, chunkSize)){
		if(write(wfd,buf,n)!=n) perror("WriteError\n");
	}
	if(n==-1) perror("ReadError\n");
	end =  time(NULL);
	printf("chunkSize [%d]Byte : %f\n",chunkSize, difftime(end,start));
	close(rfd);
	close(wfd);
	return 0;
}
