#include<cstdio>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
using namespace std;

enum {Reading=0, Writing=1, ReadAndWrite=2};
enum {SeekFromBeggining=0, SeekFromCurrent=1, SeekFromEnd=2};
// This procedure reverses the bytes in a file and writes reversed version in a new file

void Reverse(char *fromFile,char *revFile){
	// open the source file
	int fromFD = open(fromFile,Reading);
	if(fromFD<0){
		printf("Error in reading file %s\n",fromFile);
		return;
	}
	// move the internal file pointer so the next character read will be the last character of the file
	int ret = lseek(fromFD,-1,SeekFromEnd);
	if(ret<0){
		printf("Error seeking on %s\n",fromFile);
		close(fromFD);
		return;
	}
	int revFD = creat(revFile,ReadAndWrite);
	if(revFD<0){
		printf("Error in creating file %s\n",revFile);
		close(fromFD);
		return;
	}
	// Loop while reading from the end of the source file to the beginning
	while(true){
		char ch;
		int n=read(fromFD,&ch,1);
		if(n<0){
			printf("Error reading %s\n",fromFile);
			break;
		}
		n = write(revFD,&ch,1);
		if(n<0){
			printf("Error writing %s\n",revFile);
			break;
		}
		// exiting the loop if lseek returns an error
		if(lseek(fromFD,-2,SeekFromCurrent)<0)
			break;
	}
	close(fromFD);
	close(revFD);
	return;
}

int main(){
	char fromFile[50], revFile[50];
	scanf("%s%s",fromFile,revFile);
	Reverse(fromFile,revFile);
	return 0;
}
