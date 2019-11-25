#include<cstdio>
using namespace std;

bool isPrime(int n){
	if(n==0 || n==1)	return false;
	if(n==2)	return true;
	if(n%2==0)	return false;
	for(int i=3; i*i<=n; i+=2){
		if(n%i==0)	return false;
	}
	return true;
}

int main(){
	int n;
	scanf("%d",&n);
	if(isPrime(n))
		printf("Yes %d is prime\n",n);
	else
		printf("No %d is not prime\n",n);
	return 0;
}
