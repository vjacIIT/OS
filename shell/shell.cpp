#include<cstdio>
#include<unistd.h>
#include<cstdlib>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<cstring>
using namespace std;

const int ARGSIZE = 50;
const int NARGS = 20;
const int STRING = 1;
const int INREDIR = 2;
const int OUTREDIR = 3;

char *argv[NARGS];
char args[NARGS][ARGSIZE];

// By convention argv[0] must contain the file name to be executed in excv

int compare(char *str){
	int cnt = 1;
	if(strcmp(str,"logout\n")==0) return 0;
	for(int i=0; i<strlen(str); i++){
		if(str[i]==' ')	cnt++;
	}
	printf("%d\n",cnt);
	return cnt;
}

int main(){
	bool flg=false;
	int wasInRedir, wasOutRedir;
	char inRedir[ARGSIZE]={}, outRedir[ARGSIZE]={}, str[ARGSIZE]={};
	std::system("clear");
	printf("Type logout to come out\n");
	while(1){
		printf("vjac@iitpkd:~$ ");
		wasInRedir = 0;
		wasOutRedir = 0;
		int argc =0;
		int done = 0;
		char word[ARGSIZE];
		while(!done){
			//int argType = getWord(word);	there is nothing like getWord()
			int argType;
			char word[ARGSIZE];
			fgets(str,50,stdin);
			argType = compare(str);
			if(!argType){
				flg=true;
				break;
			}
			sscanf(str,"%s %s %s\n",word,inRedir,outRedir);
			argc = argType;
			switch(argType){
				case STRING:			// name of executable
					strcpy(args[0],word);
					argv[argc]=&args[argc][0];
					done = 1;
					break;
				case INREDIR:			// only input_file is given
					strcpy(args[0],word);
					argv[argc]=&args[argc][0];
					wasInRedir = 1;
					//(void)getWord(inRedir);
					done = 1;
					break;
				case OUTREDIR:			// input and output file are given
					strcpy(args[0],word);
					argv[argc]=&args[argc][0];
					wasOutRedir = 1;
					//(void)getWord(outRedir);
					done = 1;
					break;
			}
		}
		argv[argc]=NULL;
		if(flg)
			break;
		if(fork()==0){			// as shell keeps running all the time
			if(wasInRedir){
				close(0);		// close standard input
				open(inRedir,0);
			}
			if(wasOutRedir){
				close(1);		// close standard output
				enum{ UserWrite = 0755};
				creat(outRedir,UserWrite);
			}
			char cmd[60];
			strcpy(cmd,"./");
			strcat(cmd,args[0]);
			execv(cmd,&argv[0]);
			
			strcpy(cmd,"/bin/");		// it should not come here
			strcat(cmd,args[0]);
			execv(cmd,&argv[0]);
			printf("Child: could not exec \n");
			exit(1);
		}
		int status;
		(void)wait(&status);
	}
	//	finish;			nothing like finish in C++
	printf("Shell exiting \n");
	return 0;
}
