#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define INF 0x3f3f3f3f
#define MAX_N 25000
#define MAX_M 1000000
using namespace std;
struct edge{int to,cap,rev,index;};
vector<edge> G[MAX_N];
queue<int> que;
int level[MAX_N],iter[MAX_N],ans[MAX_N];
int N,M,deg[MAX_M],low[MAX_M],S = 0,T = MAX_N - 1,sum;
inline void init(){for(int i = 0;i < MAX_N;++i)G[i].clear();}
inline void add_edge(int from,int to,int cap,int id){
	G[from].push_back((edge){to,cap,G[to].size(),id});
	G[to].push_back((edge){from,0,G[from].size() - 1,0});
}
inline void bfs(int s){
	memset(level,-1,sizeof(level));
	level[s] = 0;que.push(s);
	while(!que.empty()){
		int v = que.front();que.pop();
		for(int i = 0;i < G[v].size();++i){
			const edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0){
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}
int dfs(int v,int t,int f){
	if(v == t)return f;
	for(int &i = iter[v];i < G[v].size();++i){
		edge &e = G[v][i];
		if(e.cap > 0 && level[e.to] > level[v]){
			int d = dfs(e.to,t,min(e.cap,f));
			if(d > 0){
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}
int max_flow(int s,int t){
	int flow = 0;
	for(;;){
		memset(iter,0,sizeof(iter));
		bfs(s);
		if(level[t] < 0)return flow;
		int f;
		while((f = dfs(s,t,INF)) > 0){
			flow += f;
		}
	}
}

int main(){
	while(~scanf("%d%d",&N,&M)){
		init();
		for(int i = 1,u,v,up,down;i <= M;++i){
			scanf("%d%d%d%d",&u,&v,&down,&up);//one bug here~
			add_edge(u,v,up - down,i);
			deg[u] -= down;deg[v] += down;
			low[i] = down;
		}
		for(int i = 1;i <= N;++i){
			if(deg[i] < 0)add_edge(i,T,-deg[i],0);
			if(deg[i] > 0)add_edge(S,i,deg[i],0),sum += deg[i];
		}
		int tmp = max_flow(S,T);
		if(tmp != sum)puts("NO");
		else{
			puts("YES");
			for(int i = 1;i <= N;++i){
				for(int j = 0;j < G[i].size();++j){
					const edge &e = G[i][j];
					ans[e.index] = G[e.to][e.rev].cap;
				}
			}
			for(int i = 1;i <= M;++i)printf("%d\n",ans[i] + low[i]);
		}
	}
	return 0;
}