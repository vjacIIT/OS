#include<cstdio>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<cstring>
#include<sys/wait.h>
#include<fcntl.h>
using namespace std;

int main(){
	int fd1[2];		// pipe from process 1 to 2
	int fd2[2];		// pipe fro process 2 to 1

	char fixed_str[] = "ChangeThisString";
	char input_str[100];
	pid_t p;
	if(pipe(fd1)==-1){
		printf("Pipe Failed\n");
		return 1;
	}
	if(pipe(fd2)==-1){
		printf("Pipe Failed\n");
		return 2;
	}
	scanf("%s",input_str);
	p = fork();
	if(p<0){
		printf("fork Failed\n");
		return 3;
	}
	else if(p>0){				// parent process
		char concat_str[100];
		close(fd1[0]);			// close reading end of first pipe
		write(fd1[1],input_str,strlen(input_str)+1);
		close(fd1[1]);			// close writing end of first pipe
		
		wait(NULL);			// wait for child process to end

		close(fd2[1]);			// close the writing end of second pipe		
		read(fd2[0],concat_str,100);
		printf("Concatenated string %s\n",concat_str);
		close(fd2[0]);			// close reading end of pipe second
	}
	else{						// child process
		close(fd1[1]);				// close writing end of pipe 1

		char concat_str[100];
		read(fd1[0],concat_str,100);

		int k = strlen(concat_str);
		int i;
		for(i=0; i<strlen(fixed_str); i++)
			concat_str[k++] = fixed_str[i];
		
		concat_str[k]='\0';
		close(fd1[0]);				// close reading end of pipe 1
		close(fd2[0]);				// close reading end of pipe 2
		
		write(fd2[1],concat_str,strlen(concat_str)+1);
		close(fd2[1]);				// close writing end of pipe 2
		exit(0);
	}
	return 0;
}
