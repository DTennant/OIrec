#include <cstdio>
#include <cstring>
#include <queue>
#define MAX_N 100100
using namespace std;
queue<int> que;
struct edge{int to,cost,next;}es[MAX_N << 2];
int n,k,cnt,head[MAX_N],inque_time[MAX_N],inque[MAX_N],dis[MAX_N];
long long ans;
inline void init(){cnt = 0;memset(head,-1,sizeof(head));}
inline void add_edge(int from,int to,int cost){
	es[cnt].to = to;es[cnt].cost = cost;
	es[cnt].next = head[from];head[from] = cnt++;
}
bool spfa(int st){
	que.push(st);inque[st] = true;
	inque_time[st]++;
	while(!que.empty()){
		int u = que.front();que.pop();
		inque[u] = false;
		for(int i = head[u];~i;i = es[i].next){
			int v = es[i].to,w = es[i].cost;
			if(dis[v] < dis[u] + w){
				dis[v] = dis[u] + w;
				if(++inque_time[v] >= n)return true;
				if(!inque[v]){
					inque[v] = true;
					que.push(v);
				}
			}
		}
	}
	return false;
}
int main(){
	init();
	scanf("%d%d",&n,&k);
	static int x,a,b;
	while(k--){
		scanf("%d%d%d",&x,&a,&b);
		switch(x){
			case 1:add_edge(a,b,0);add_edge(b,a,0);break;
			case 2:if(a == b){puts("-1");return 0;}add_edge(a,b,1);break;
			case 3:add_edge(b,a,0);break;
			case 4:if(a == b){puts("-1");return 0;}add_edge(b,a,1);break;
			case 5:add_edge(a,b,0);break;
		}
	}
	for(int i = n;i > 0;--i)add_edge(0,i,1);
	if(spfa(0)){puts("-1");return 0;}
	for(int i = 1;i <= n;++i)ans += dis[i];
	printf("%lld\n",ans);
	return 0;
}