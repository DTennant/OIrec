#include <cstdio>
#include <cstring>
#define MAX_N 600
using namespace std;
int N,K,match[MAX_N];
bool used[MAX_N],G[MAX_N][MAX_N];
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
	scanf("%d%d",&N,&K);
	for(int i = 1,a,b;i <= K;++i){
		scanf("%d%d",&a,&b);
		G[a][b] = true;
	}
	printf("%d\n",bipartite_matching());
	return 0;
}