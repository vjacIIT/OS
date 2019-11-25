#include<cstdio>
using namespace std;

int gcd(int a, int b){
	if(a==0) return b;
	return gcd(b%a,a);
}

int main(){
	int a, b;
	scanf("%d%d",&a,&b);
	a = gcd(a,b);
	printf("gcd is %d\n",a);
	return 0;
}
