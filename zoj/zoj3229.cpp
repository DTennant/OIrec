#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX_N 2500
#define INF 0x3f3f3f3f
using namespace std;
struct edge{int to,cap,rev,id;};
vector<edge> G[MAX_N];
queue<int> que;
int level[MAX_N],iter[MAX_N],deg[MAX_N],low[366 * 1000],N,M;
int S = 0,T = MAX_N - 1,SS = MAX_N - 2,ST = MAX_N - 3,index,ans[366 * 1000];
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
		init();memset(id,0,sizeof(id));
		for(int i = 1,g;i <= M;++i){
			scanf("%d",&g);
			add_edge(i + N,T,INF - g);
			deg[i + N] -= g;
		}
		for(int i = 1,C,D;i <= N;++i){
			scanf("%d%d",&C,&D);
			add_edge(S,i,D);
			for(int j = 1,g,L,R;j <= C;++j){
				scanf("%d%d%d",&g,&L,&R);
				deg[i] -= L;deg[g + N] += L;low[-~index] = L;
				add_edge(i,g + N,R - L,++index);
			}
		}
		add_edge(T,S,INF);
		int sum = 0;
		for(int i = 1;i <= M + N;++i){
			if(deg[i] > 0)add_edge(SS,i,deg[i]),sum += deg[i];
			if(deg[i] < 0)add_edge(i,ST,-deg[i]);
		}
		int tmp = max_flow(SS,ST);
		if(tmp != sum)puts("-1");
		else{
			printf("%d\n",max_flow(S,T));
			for(int i = 1;i <= MAX_N;++i){
				for(int j = 0;j < G[i].size();++j){
					const edge &e = G[i][j];
					if(e.id != 0){
						ans[e.id] = G[e.to][e.rev].cap;
					}
				}
			}
			for(int i = 1;i <= index;++i){
				printf("%d\n",ans[i] + low[i]);
			}
		}
		putchar('\n');
	}
	return 0;
}