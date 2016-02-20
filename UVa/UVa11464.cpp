#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 0x3f3f3f3f
#define MAX_N 25
using namespace std;
int T,N,A[MAX_N][MAX_N],B[MAX_N][MAX_N];
int check(int s){
	memset(B,0,sizeof(B));
	for(int c = 0;c < N;++c){
		if(s & (1 << c))B[0][c] = 1;
		else if(A[0][c] == 1) return INF;
	}
	for(int r = 1;r < N;++r){
		for(int c = 0;c < N;++c){
			int sum = 0;
			if(r > 1)sum += B[r - 2][c];
			if(c > 0)sum += B[r - 1][c - 1];
			if(c < N)sum += B[r - 1][c + 1];
			B[r][c] = sum % 2;
			if(A[r][c] == 1 && B[r][c] == 0)return INF;
		}
	}
	int cnt = 0;
	for(int r = 0;r < N;++r){
		for(int c = 0;c < N;++c){
			if(A[r][c] != B[r][c])++cnt;
		}
	}
	return cnt;
}
int main(){
	scanf("%d",&T);
	for(int kase = 1;kase <= T;++kase){
		int ans = INF;
		scanf("%d",&N);
		for(int i = 0;i < N;++i){
			for(int j = 0;j < N;++j){
				scanf("%d",&A[i][j]);
			}
		}
		for(int s = 0;s < (1 << N);++s){
			ans = min(ans,check(s));
		}
		printf("Case %d: %d\n",kase,ans == INF ? -1 : ans);
	}
	return 0;
}