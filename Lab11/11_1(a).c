#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>

struct mymsgbuf{
	long mtype;
	char mtext[80];
};

int main(int argc, char* argv[]){
	key_t key;
	int msgid;
	struct mymsgbuf msg;
	if(strcmp(argv[1],"-s")==0){
		key=ftok("pig",1);
		msgid = msgget(key,IPC_CREAT|0644);
		msg.mtype=1;
		strcpy(msg.mtext,argv[2]);
		msgsnd(msgid,(void*)&msg,80,IPC_NOWAIT);
	}
	else if(strcmp(argv[1],"-r")==0){
		key=ftok("pig",1);
		msgid=msgget(key,IPC_CREAT|0644);
		while(msgrcv(msgid,&msg,80,0,IPC_NOWAIT)!=-1){
			printf("%s\n",msg.mtext);
		}
		msgctl(msgid,IPC_RMID,(struct msqid_ds*) NULL);
	}
	else printf("wrong input\n");
	return 0;
}
