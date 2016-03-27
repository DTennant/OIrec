#include <cstdio>
#define MAX_N 35
using namespace std;
long long dp[MAX_N],N;
int main(){
	dp[0] = 1;dp[2] = 3;
	for(int i = 4;i < 35;i += 2)dp[i] = 4 * dp[i - 2] - dp[i - 4];
	while(~scanf("%lld",&N))if(N != -1)printf("%lld\n",dp[N]);
	return 0;
}