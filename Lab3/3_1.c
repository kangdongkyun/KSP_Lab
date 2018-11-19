#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct User {
int mID;
int mScore[10];
};

void main(int argc, char* argv[]) {
FILE *rfp1, *rfp2;
int n;
struct User binary;
struct User text;
clock_t start1, start2, end1, end2;
if((rfp1 = fopen(argv[1], "r"))==NULL) {
perror("fopen: test.bin");
exit(1);
}

start1 = clock();
int itemSize = sizeof(struct User);
while((n=fread(&binary, itemSize, 1, rfp1)) > 0) {


}
end1 = clock();

if((rfp2 = fopen(argv[2], "r")) == NULL) {
perror("fopen: test.txt");
exit(2);
}

start2 = clock();
while((n=fscanf(rfp2, "%d %d %d %d %d %d %d %d %d %d %d", &text.mID, &text.mScore[0], &text.mScore[1],&text.mScore[2],&text.mScore[3],&text.mScore[4],&text.mScore[5],&text.mScore[6],&text.mScore[7],&text.mScore[8],&text.mScore[9]))) {

}
end2 = clock();

printf("binaryfile 걸린시간 : %f \n", (float)(end1- start1)/CLOCKS_PER_SEC);
printf("textfile 걸린 시간 : %f \n", (float)(end2-start2)/CLOCKS_PER_SEC);

fclose(rfp1);
fclose(rfp2);
}

