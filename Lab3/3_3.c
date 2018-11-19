#include <stdlib.h> 
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void main(int argc, char* argv[]) {
int rfd, n, temp;
FILE  *wfp;
unsigned char buf[3];

if ((rfd = open(argv[1], O_RDONLY)) == -1) {
perror("open: Lab3_3_input"); 
exit(1);
}

if((wfp = fopen(argv[2], "w")) == NULL) {
perror("fopen: output");
exit(2);
}

while((n = read(rfd, buf, 3)) > 0) {
temp = buf[2]+(buf[1] << 8) + (buf[0]<<16);
fprintf(wfp, "%d ", temp);
}

close(rfd);
fclose(wfp);
}

