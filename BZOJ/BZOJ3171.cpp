#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define INF 0x3f3f3f3f
#define MAX_N 800
using namespace std;
struct edge{int from,to,cap,flow,cost;};
struct MCMF{
	int n,m,s,t;
	vector<edge> edges;
	vector<int> G[MAX_N];
	int inq[MAX_N],a[MAX_N],d[MAX_N],p[MAX_N];
	void init(int n){
		this->n = n;
		for(int i = 0;i < n;++i)G[i].clear();
		edges.clear();
	}
	void add_edge(int from,int to,int cap,int cost){
		edges.push_back((edge){from,to,cap,0,cost});
		edges.push_back((edge){to,from,0,0,-cost});
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}
	bool BellmanFord(int s,int t,int &flow,int &cost){
		for(int i = 0;i < n;++i)d[i] = INF;
		d[s] = 0;inq[s] = 1;a[s] = INF;p[s] = 0;
		queue<int> que;
		que.push(s);
		while(!que.empty()){
			int u = que.front();que.pop();inq[u] = 0;
			for(int i = 0;i < G[u].size();++i){
				edge &e = edges[G[u][i]];
				if(e.cap > e.flow && d[e.to] > d[u] + e.cost){
					d[e.to] = d[u] + e.cost;
					p[e.to] = G[u][i];
					a[e.to] = min(a[u],e.cap - e.flow);
					if(!inq[e.to]){que.push(e.to);inq[e.to] = 1;}
				}
			}
		}
		if(d[t] == INF)return false;
		flow += a[t];
		cost += a[t] * d[t];
		int u = t;
		while(u != s){
			edges[p[u]].flow += a[t];
			edges[p[u]^1].flow -= a[t];
			u = edges[p[u]].from;
		}
		return true;
	}
	int min_cost(int s,int t){
		int flow = 0,cost = 0;
		while(BellmanFord(s,t,flow,cost));
		return cost;
	}
}solver;
const int dx[4]={0,0,-1,1},dy[4]={-1,1,0,0};
int n,m,mark[MAX_N][MAX_N],map[MAX_N][MAX_N],S = 0,T = 699;
inline void build(void){
	for(int i = 1;i <= n * m;++i)solver.add_edge(S,i,1,0);
	for(int i = 1;i <= n * m;++i)solver.add_edge(i + 300,T,1,0);
	for(int i = 1;i <= n;++i){
		for(int j = 1;j <= m;++j){
			for(int k = 0;k < 4;++k){
				int nx = i + dx[k],ny = j + dy[k];
				if(nx < 1)nx = n;if(nx > n)nx = 1;
				if(ny < 1)ny = m;if(ny > m)ny = 1;
				solver.add_edge(mark[i][j],mark[nx][ny] + 300,1,k != map[i][j]);
			}
		}
	}
}
int main(){
	solver.init(700);
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i){
		for(int j = 1;j <= m;++j){
			mark[i][j] = (i - 1) * m + j;
		}
	}
	for(int i = 1;i <= n;++i){
		char ch[20];
		scanf("%s",ch + 1);
		for(int j = 1;j <= m;++j){
			if(ch[j] == 'L')map[i][j] = 0;
			if(ch[j] == 'R')map[i][j] = 1;
			if(ch[j] == 'U')map[i][j] = 2;
			if(ch[j] == 'D')map[i][j] = 3;
		}
	}
	build();
	printf("%d\n",solver.min_cost(S,T));
	return 0;
}