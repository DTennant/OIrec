//UVaLive3902.cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX_N 1100
using namespace std;
vector<int> gr[MAX_N],nodes[MAX_N];
int N,S,K,fa[MAX_N],T;
bool covered[MAX_N];
void dfs(int u,int f,int d){
	fa[u] = f;
	int nc = gr[u].size();
	if(nc == 1 && d > K)nodes[d].push_back(u);
	for(int i = 0;i < nc;++i){
		int v = gr[u][i];
		if(v != f)dfs(v,u,d + 1);
	}
}
void dfs2(int u,int f,int d){
	covered[u] = true;
	int nc = gr[u].size();
	for(int i = 0;i < nc;++i){
		int v = gr[u][i];
		if(v != f && d < K)dfs2(v,u,d + 1);
	}	
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&N,&S,&K);
		for(int i = 1;i <= N;++i)gr[i].clear(),nodes[i].clear();
		for(int i = 0,a,b;i < N - 1;++i){
			scanf("%d%d",&a,&b);
			gr[a].push_back(b);
			gr[b].push_back(a);
		}
		dfs(S,-1,0);
		int ans = 0;
		memset(covered,false,sizeof(covered));
		for(int i = N - 1;i > K;--i){
			for(int j = 0;j < nodes[i].size();++j){
				int u = nodes[i][j];
				if(covered[u])continue;
				for(int k = 0;k < K;++k)u = fa[u];
				dfs2(u,-1,0);
				++ans;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}