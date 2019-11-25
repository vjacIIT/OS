#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/msg.h>
using namespace std;

struct mesg_buffer{
	long msg_type;
	char mesg_text[100];
} message;

int main(){
	key_t key;
	int msgid;
	
	key = ftok("progfile",65);			// Same key is already generated in sender file
	msgid = msgget(key,0666 | IPC_CREAT);	// Returns already made mess_qid
	
	msgrcv(msgid,&message,sizeof(message),1,0);
	
	printf("Data Received is: %s",message.mesg_text);
	msgctl(msgid,IPC_RMID,NULL);			// destroy message queue
	
	return 0;
}
