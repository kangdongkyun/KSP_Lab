#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>

int main(){
	int rfd, n;

	clock_t start, end;
	rfd = open("Lab2_3_message.txt",O_RDONLY);
	if(rfd == -1){
		perror("RfdopenError\n");
		exit(1);
	}
	size_t fileSize = lseek(rfd, 0, SEEK_END);
	char* buf = (char*)malloc(sizeof(char) * fileSize);
	lseek(rfd,0,SEEK_SET);
	start = time(NULL);
	n=read(rfd,buf,fileSize);
	for(int i=0;i<fileSize;i++){
		if(buf[i]>=32 && buf[i]<=127){
			printf("%c",buf[i]);

		}
		else{
			i=i+(buf[i]%32);
		}
	}
	end = time(NULL);
	printf("\nit takes %f sec\n",difftime(end,start));
	close(rfd);
	free(buf);
	return 0;
}
