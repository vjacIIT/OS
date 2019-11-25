#include<cstdlib>
#include<cstdio>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
using namespace std;

int main(int argc, char **argv){
	int pid, ret, status;
	char *myargs[] = {NULL};
	char *myenv[] = {NULL};
	printf("Parent: HELLO, WORLD!\n");
	pid = fork();
	if(pid==0)
		execve("child",myargs,myenv);
	printf("Parent: Waiting for child to complete\n");
	if((ret=waitpid(pid,&status,0))==-1)
		printf("parent:error\n");
	if(ret==pid)
		printf("Parent: Child process waited for \n");
	return 0;
}
