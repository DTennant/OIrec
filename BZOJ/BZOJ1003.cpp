#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAX_N 110
#define MAX_M MAX_N * MAX_N
#define INF 0x3f3f3f3f
using namespace std;
struct edge{int to,cost,next;}es[MAX_M];
int head[MAX_N],cnt;
inline void init(){cnt = 0;memset(head,-1,sizeof(head));}
inline void add_edge(int from,int to,int cost){
	es[cnt].to = to,es[cnt].cost = cost;
	es[cnt].next = head[from];head[from] = cnt++;
}
queue<int> que;
bool inque[MAX_N],ban[MAX_N][MAX_N],used[MAX_N];
int dist[MAX_N],dp[MAX_N],cost[MAX_N][MAX_N];
void spfa(int st){
	memset(inque,false,sizeof(inque));
	memset(dist,INF,sizeof(dist));
	que.push(st);inque[st] = true;dist[st] = 0;
	while(!que.empty()){
		int u = que.front();que.pop();
		inque[u] = false;
		for(int i = head[u];~i;i = es[i].next){
			int v = es[i].to,w = es[i].cost;
			if(used[v])continue;
			if(dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
				if(!inque[v]){
					que.push(v);inque[v] = true;
				}
			}
		}
	}
}
int main(){
	int n,m,K,e,d;
	init();
	scanf("%d%d%d%d",&n,&m,&K,&e);
	for(int i = 1,a,b,c;i <= e;++i){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);add_edge(b,a,c);
	}
	scanf("%d",&d);
	for(int i = 1,a,b,c;i <= d;++i){
		scanf("%d%d%d",&c,&a,&b);
		for(int j = a;j <= b;++j)ban[c][j] = true;
	}
	for(int i = 1;i <= n;++i){
		for(int j = i;j <= n;++j){
			memset(used,false,sizeof(used));
			for(int k = i;k <= j;++k){
				for(int z = 2;z < m;++z){
					if(ban[z][k])used[z] = true;
				}
			}
			spfa(1);
			cost[i][j] = dist[m] * (dist[m] >= INF ? 1 : (j - i + 1));
		}
	}
	memset(dp,INF,sizeof(dp));
	dp[0] = 0;
	for(int i = 1;i <= n;++i){
		for(int j = 0;j < i;++j){
			dp[i] = min(dp[i],dp[j] + cost[j + 1][i] + K);
		}
	}
	printf("%d\n",dp[n] - K);
	return 0;
}