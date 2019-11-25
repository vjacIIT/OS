#include<cstdio>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
using namespace std;

enum{ Reading=0, Writing=1, ReadAndWrite=2};

int main(){
	char * argv[] = {"./receiver","PipeToReceiver","PipeToSender"};
	int count=0;
	// First argument is pipe to read from
	int from_pipe = open(argv[1], Reading);
	while(1){
		char ch;
		int n = read(from_pipe,&ch,1);
		if(n==0)
			break;
		++count;
	}
	close(from_pipe);
	// send the count back to the sender
	// Second argument is the pipe to write to
	int to_pipe = open(argv[2], Writing);
	write(to_pipe,&count,4);			// 4 bytes int
	close(to_pipe);
	exit(0);
	return 0;
}
