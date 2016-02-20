#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define INF 0x3f3f3f3f
#define MAX_N 110
#define MAX_M MAX_N * MAX_N / 2
using namespace std;
struct edge{int to,cap,rev,index;};
vector<edge> G[MAX_N];
queue<int> que;
int level[MAX_N],iter[MAX_N],ans[MAX_N];
int N,M,deg[MAX_M],S,T,sum,SS = MAX_N - 1,ST = SS - 1;
inline void init(){for(int i = 0;i < MAX_N;++i)G[i].clear();}
void add_edge(int from,int to,int cap,int id){
	G[from].push_back((edge){to,cap,G[to].size(),id});
	G[to].push_back((edge){from,0,G[from].size() - 1,0});
}
void add_edge(int from,int to,int cap){
	G[from].push_back((edge){to,cap,G[to].size(),0});
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
		init();memset(deg,0,sizeof(deg));S = 1;T = N;
		for(int i = 1,u,v,c,k;i <= M;++i){
			scanf("%d%d%d%d",&u,&v,&c,&k);
			if(k)deg[u] -= c,deg[v] += c,ans[i] = c;
			else add_edge(u,v,c,i);
		}
		for(int i = 1;i <= N;++i){
			if(deg[i] > 0)add_edge(SS,i,deg[i]),sum += deg[i];
			if(deg[i] < 0)add_edge(i,ST,-deg[i]);
		}
		max_flow(SS,ST);
		add_edge(T,S,INF);
		int tmp = max_flow(SS,ST);
		if(sum != tmp)puts("Impossible");
		else{
			edge e;
			for(int i = 0;i < G[T].size();++i){
				e = G[T][i];
				if(e.to == S)break;
			}
			printf("%d \n",G[e.to][e.rev].cap);
			for(int i = 1;i <= N;++i){
				for(int j = 0;j < G[i].size();++j){
					const edge &e = G[i][j];
					ans[e.index] = G[e.to][e.rev].cap;
				}
			}
			for(int i = 1;i <= M;++i){
				if(i != M)printf("%d ",ans[i]);
				else printf("%d \n",ans[i]);
			}
		}
	}
	return 0;
}