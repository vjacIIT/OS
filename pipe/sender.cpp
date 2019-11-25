#include<cstdio>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
using namespace std;

enum{Reading=0, Writing=1, ReadAndWrite=2};

int main(){
	char * argv[] = {"./sender","fileToRead","PipeToReceiver","PipeToSender"}; 
	printf("came here\n");
	// First argument is the file to open
	int fromFD = open(argv[1],Reading);

	// Second argument is pipe to write on
	int to_pipe = open(argv[2],Writing);
	while(1){
		char ch;
		int n = read(fromFD, &ch, 1);
		printf("%c\n",ch);
		if(n==0)
			break;
		write(to_pipe,&ch,1);
	}
	close(fromFD);
	// Closing the pipe will cause the receiver to get an end of file after it reads
	// all the characters currently in the pipe
	close(to_pipe);
	// Third argument is pipe from which to read the count
	int from_pipe= open(argv[3],Reading);
	int n;
	read(from_pipe,&n,4);		// int is 4 bytes
	close(from_pipe);
	printf("%d characters\n",n);
	exit(0);
	return 0;
}
