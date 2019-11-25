#include<cstdio>
#include<unistd.h>
#include<cstdlib>
#include<sys/types.h>
#include<sys/wait.h>
#include<iostream>
#include<fstream>
#include<fcntl.h>
using namespace std;

enum {Reading=0, Writing=1, ReadAndWrite=2, ReadWriteFile=0644};
// This procedure takes as arguments two file path names
// The first file is copied to the second file

void FileCopy(char *fromFile, char *toFile){
	// open the source file for reading, i.e. fromFile
	int fromFD = open(fromFile,Reading);
	if(fromFD<0){
		printf("Error opening %s file\n",fromFile);
		return;
	}
	// create the destination file with protection mode read and write
	int toFD = creat(toFile,ReadAndWrite);
	if(toFD<0){
		printf("Error opening %s file\n",toFile);
		close(fromFD);			// closing the from file
		return;
	}
	// THis loop reads one character at a time from the souce file
	// And writes it to the destination file
	while(true){
		char ch;
		int n = read(fromFD,&ch,1);			// read(fileID,char* buffer,count)
		// if 0 characters were read, we are at end of the file
		if(n<=0)
			break;
		// throw away the value returned by write
		n = write(toFD, &ch, 1);
		if(n<0){
			printf("Error writing %s file\n",toFile);
			break;
		}
	}
	// close the opened files and return
	close(fromFD);				// this takes fileID not char *
	close(toFD);
	return;
}

int main(){
	char fromFile[50], toFile[50];
	scanf("%s%s",fromFile,toFile);
	FileCopy(fromFile,toFile);
	return 0;
}
