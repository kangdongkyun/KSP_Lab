#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#define Process_num 4

struct Processes {
int a_Time;
int b_Time;
char name[2];
};

void main(int argc, char* argv[]) {
struct Processes p[Process_num];

p[0].name[0] = 'A';
p[1].name[1] = 'B';
p[2].name[2] = 'C';
p[3].name[3] = 'D';

FILE *rfp;
int n = 0, i = 0, time = 0, r = 0;
char result[100] = "";
if((rfp = fopen("input.txt", "r")) == NULL ) {
perror("fopen : input.txt");
exit(1);
}

while((n = fscanf(rfp, "%d %d %d %d", &p[0].a_Time, &p[1].a_Time, &p[2].a_Time, &p[3].a_Time)) != EOF) {
fscanf(rfp, "%d %d %d %d", &p[0].b_Time, &p[1].b_Time, &p[2].b_Time, &p[3].b_Time);
}

while(1) {
if(i==4) break;
if(time < p[i].a_Time) {
result[r] = 'X';
time++;
r++;
continue;
}
if(p[i].b_Time > 0) {
result[r] = p[i].name[i];
time++;
p[i].b_Time--;
r++;
continue;
}
else {
i++;
continue;
}
}
printf("\nChart : %s \n", result);

fclose(rfp);
}
