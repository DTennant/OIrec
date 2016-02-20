#include <cstdio>
#include <cstring>
#define MAX_N 150
using namespace std;
int match[MAX_N],N,M;
bool G[MAX_N][MAX_N],used[MAX_N];
bool dfs(int v){
	for(int i = 1;i <= N;++i){
		if(!used[i] && G[v][i]){
			used[i] = true;
			if(match[i] == -1 || dfs(match[i])){
				match[i] = v;
				return true;
			}
		}
	}
	return false;
}
int bipartite_matching(){
	int ans = 0;
	memset(match,-1,sizeof(match));
	for(int i = 1;i <= N;++i){
		memset(used,false,sizeof(used));
		if(dfs(i))++ans;
	}
	return ans;
}
int main(){
	scanf("%d%d",&N,&M);
	for(int i = 0,a,b;i < M;++i){
		scanf("%d%d",&a,&b);
		G[a][b] = true;
	}
	for(int k = 1;k <= N;++k){
		for(int i = 1;i <= N;++i){
			for(int j = 1;j <= N;++j){
				G[i][j] |= G[i][k] & G[k][j];
			}
		}
	}
	printf("%d\n",N - bipartite_matching());
	return 0;
}