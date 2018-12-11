#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>

#define MAXTEXT 100

struct mymsgbuf{
	long mtype;
	char mtext[MAXTEXT];
};
int main(int argc, char* argv[]){
	key_t key;
	int msgid;
	struct mymsgbuf msg;
	for(int i=0;i<atoi(argv[1]);i++){
		printf("%d번째 메시지입니다.\n",i);
		printf("보낼 메시지 내용을 입력하세요. : ");
		fgets(msg.mtext,MAXTEXT,stdin);
		
		key = ftok("keyfile",1);
		msgid = msgget(key,IPC_CREAT|0644);
		msg.mtype=1;
		if(msgsnd(msgid,(void*)&msg,MAXTEXT,IPC_NOWAIT)==-1){
			perror("msgsnd");exit(0);
		}
	}
	printf("\n메시지 전송 완료\n");
	return 0;
}

