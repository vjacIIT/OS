#includ<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main(){
	printf("PID of exc1 is %d\n",getpid());
	char *args[] = {"HELLO", "FRIENDS", NULL};
	execv("./exc2",args);		// runs another program named exc2 in same folder
	printf("Back to exc1\n");	// This is not printed as this program ended at execv call
	return 0;
}
