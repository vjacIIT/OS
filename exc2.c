#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main(){
	printf("IN process exc2\n");
	printf("PID is %d\n",getpid());		// PID is same as that of exec 1 program
	return 0;
}
