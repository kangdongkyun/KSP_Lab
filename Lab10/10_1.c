#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int main(void) {
        int fd[2];
        int box;
        int bead[100];
        int moves = 0;
        int sum =0;
	double avg=0.0;
	pid_t pid;
        printf("총 박스의 개수를 입력하시오 : ");
        scanf("%d", &box);

        for(int i = 0; i < box; i++) {
                printf("%d번 주머니의 구슬 개수를 입력하시오 : ", i + 1);
                scanf("%d", &bead[i]);
        }

        pipe(fd);
	switch(pid=fork()){
	case -1:perror("fork");exit(0);break;
	case 0:
		close(fd[0]);
		write(fd[1],&box,sizeof(int));
		printf("Parent send value of num_box : %d\n",box);
		for(int i=0;i<box;i++){
			write(fd[1],&bead[i],sizeof(int));
			printf("parent send value of num_Bead[%d] : %d \n", i+1,bead[i]);
		}
		break;
	default:	
		close(fd[1]);
		read(fd[0],&box,sizeof(int));
		printf("Child received value of num_Box : %d\n",box);
		for(int i=0;i<box;i++){
			read(fd[0],&bead[i],sizeof(int));
			printf("Child received value of num_Bead[%d] : %d\n",i+1,bead[i]);
			sum=sum + bead[i];
		}
		if(sum%box!=0) moves = -1;
		else{
			avg = sum / box;
			for(int i = 0;i<box;i++){
				if(bead[i]<avg) moves += avg-bead[i];
			}
		}
		if(moves == -1) printf("구슬이 똑같이 나눠지지 않습니다.\n");
		else {printf("누적이동수 : %d\n",moves);}
		break;
	}
        return 0;
}
