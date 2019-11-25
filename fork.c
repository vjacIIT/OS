#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
	int cnt=1;
	printf("Here for the first time\n");
	fork();
	printf("first count is %d\n",++cnt);
	cnt++;
	fork();
	printf("second count is %d\n",++cnt);
	return 0;
}	
