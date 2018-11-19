#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int compareString(char* ch1, char* ch2){
	int q=0,w=0;
	while(*(ch1 + q) != '\0') q++;
	while(*(ch2 + w) != '\0') w++;
	if(q!=w) return 0;
	w=0;
	for(int i=0;i<q;i++){
		if(*(ch1+i)==*(ch2+i)){
			w++;
		}
	}
	if(q==w) return 1;
	else return 0;
}
int divide(char* ch, char* buf, int offset){
	int i,count=0;
	for(i=offset;*(ch+i)!=' ';i++){
		if(*(ch+i)=='\0') break;
		*(buf + count) = *(ch+i);
		count++;
	}
	return i+1;
}
int main(int argc, char* argv[]) {
	int rfd, n,count =0;
	char* ch;
	char buf[55]={'\0'};
	int offset=0;
	clock_t start, end;
	rfd = open("junk.txt", O_RDONLY);
	if(rfd == -1){
		perror("Error");
		exit(1);
	}
	size_t fileSize = lseek(rfd, 0, SEEK_END);
	lseek(rfd,0,SEEK_SET);
	ch=(char*)malloc(sizeof(char)*fileSize);
	n = read(rfd, ch, fileSize);
	start = time(NULL);
	while(*(ch+offset)!='\0'){
		offset = divide(ch,buf,offset);
		if(compareString(*(argv+1),buf)==1){
			count++;
			printf("%s, %s : match!!\n",*(argv+1), buf);
		}
		for(int i=0;i<55;i++) buf[i]='\0';
	}
	end = time(NULL);
	printf("# of '%s' in the text file is %d\n",*(argv+1),count);
	free(ch);
	close(rfd);
	return 0;
}


