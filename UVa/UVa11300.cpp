#include <cstdio>
#include <algorithm>
#define MAX_N 1000100
using namespace std;
typedef long long ll;
ll A[MAX_N],C[MAX_N],ans,N,sum,avr;
int main(){
	while(~scanf("%d",&N)){
		sum = 0;
		for(int i = 1;i <= N;++i){
			scanf("%lld",A + i);
			sum += A[i];
		}
		avr = sum / N;C[0] = 0;
		for(int i = 1;i < N;++i)C[i] = C[i - 1] + A[i] - avr;
		sort(C,C + N);
		ll x1 = C[N / 2],ans = 0;
		for(int i = 0;i < N;++i)ans += abs(x1 - C[i]);
		printf("%lld\n",ans);
	}
	return 0;
}