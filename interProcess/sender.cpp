#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/ipc.h>			// ipc for inter process communication
#include<sys/msg.h>			// message queue
using namespace std;

struct mesg_buffer{
	long mesg_type;
	char mesg_text[100];
} message;

int main(){
	key_t key;
	int msgid;
	
	key = ftok("progfile",65);		// used to generate a unique key
	msgid = msgget(key, 0666 | IPC_CREAT);	//returns mess_qid (new mess_q or already present one) 
	message.mesg_type = 1;
	
	printf("Write DATA :");
	fgets(message.mesg_text,100,stdin);
	
	msgsnd(msgid,&message,sizeof(message),0);		// data is placed on a message queue
	
	printf("Data send is: %s",message.mesg_text);
	return 0;
}
