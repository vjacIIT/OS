#include<cstdio>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
using namespace std;

int main(){
	int status, ret1, ret2;
	char *args1[] = {"./sender","fileToRead","PipeToReceiver","PipeToSender"};
	char *args2[] = {"./receiver","PipeToRceiver","PipeToSender"};
	int pid1 = fork();
	if(pid1!=0){
		printf("First child\n");
		execv("./sender",args1);
	}
	if((ret1=waitpid(pid1,&status,0)==-1))
		printf("parent:error\n");
	int pid2 = fork(); 
	if(pid2!=0){
		printf("Second child\n");
		execv("./receiver",args2);
	}
	if((ret2=waitpid(pid2,&status,0)==-1))
		printf("parent2:error\n");

	//int pid1 = CreateProcessWithArgs("FileSend","FileToSend","PipeToReceiver","PipeToSender")
	//int pid2 = CreateProcessWithArgs("FileReceiver","PipeToReceiver","PipeToSender");
	exit(0);
	return 0;
}
// Main problem in the program is I don't know how to implement pipes
// Don't know what to write in PipeToReceiver and PipeToSender
// CreateProcess can be done using fork and execv,
// Tried but something is wrong, it is not even going in sender executable file
