#include <cstdio>
#include <cstring>
#define MAX_N 120
using namespace std;
int match[MAX_N],N,M,K;
bool G[MAX_N][MAX_N],used[MAX_N];
bool dfs(int v){
	for(int i = 1;i <= M;++i){
		if(!used[i] && G[v][i]){
			used[i] = true;
			if(match[i] == -1 || dfs(match[i])){
				match[i] = v;
				return true;
			}
		}
	}
	return 0;
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
	while(~scanf("%d%d%d",&N,&M,&K),N){
		memset(G,false,sizeof(G));
		for(int i = 0,a,b;i < K;++i){
			scanf("%*d%d%d",&a,&b);
			G[a][b] = true;
		}
		printf("%d\n",bipartite_matching());
	}
	return 0;
}