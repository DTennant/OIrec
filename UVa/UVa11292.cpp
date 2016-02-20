#include <cstdio>
#include <algorithm>
#define MAX_N 20100
using namespace std;
int A[MAX_N],B[MAX_N],N,M,cur,ans;
int main(){
	while(scanf("%d%d",&N,&M),N + M){
		ans = cur = 0;
		for(int i = 0;i < N;++i){
			scanf("%d",A + i);
		}
		for(int i = 0;i < M;++i){
			scanf("%d",B + i);
		}
		sort(A,A + N);sort(B,B + M);
		for(int i = 0;i < M;++i){
			if(B[i] >= A[cur]){
				ans += B[i];
				if(++cur == N)break;
			}
		}
		if(cur < N)puts("Loowater is doomed!");
		else printf("%d\n",ans);
	}
	return 0;
}