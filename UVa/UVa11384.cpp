#include <cstdio>
int N;
int F(int n){
	return n == 1 ? 1 : F(n / 2) + 1;
}
int main(){
	while(~scanf("%d",&N)){
		printf("%d\n",F(N));
	}
	return 0;
}