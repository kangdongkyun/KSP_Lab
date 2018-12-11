#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#define MAXTEXT 100

struct mymsgbuf{
	long mtype;
	char mtext[MAXTEXT];
};

int main(int argc,char* argv[]){
	char** banned;
	struct mymsgbuf inmsg;
	key_t key;
	int msgid,w_len,m_len;
	for(int i=0;i<argc-1;i++){
		printf("word[%d] : %s\n",(i+1),argv[i+1]);
		w_len = strlen(argv[i+1])+1;
		banned[i] = (char*)malloc(sizeof(char)*w_len);
		strcpy(banned[i],argv[i+1]);
	}
	key = ftok("keyfile",1);
        if ((msgid = msgget(key, 0)) < 0) {
                perror("msgget");
                exit(1);
        }
	while(1){
		m_len = msgrcv(msgid,&inmsg,MAXTEXT,0,IPC_NOWAIT);
		if(m_len==-1){
			printf("읽을 메시지가 없습니다.\n");exit(0);
		}
		printf("\n메시지를 수신합니다.\n");
		for(int i=0;i<(sizeof(banned) / sizeof(banned[0]));i++){
			if(strstr(inmsg.mtext,argv[i])!=NULL){
				printf("이 메시지는 금지된 단어가 포함되었습니다.\n");
				msgctl(msgid,IPC_RMID,(struct msqid_ds*)NULL);
				exit(1);
			}
		}
		printf("이 메시지는 금지된 단어가 없습니다.\n");
		printf("received Msg = %s", inmsg.mtext);
	}
	msgctl(msgid,IPC_RMID,(struct msqid_ds*)NULL);
	return 0;	
}
