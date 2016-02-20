#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX_N 2000
#define MAX_M 1000
#define INF 0x3f3f3f3f
using namespace std;
struct edge{int to,cap,rev;};
vector<edge> G[MAX_N];
queue<int> que;
int level[MAX_N],iter[MAX_N],cow[MAX_N],N,M,S,T,last[MAX_N];
inline void init(){for(int i = 0;i < MAX_N;++i)G[i].clear();}
inline void add_edge(int from,int to,int cap){
    G[from].push_back((edge){to,cap,G[to].size()});
    G[to].push_back((edge){from,0,G[from].size() - 1});
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
    scanf("%d%d",&M,&N);S = 0,T = N + 1;
    for(int i = 1;i <= M;++i){
        scanf("%d",cow + i);
    }
    memset(last,-1,sizeof(last));
    for(int i = 1,k;i <= N;++i){
        scanf("%d",&k);
        for(int j = 1,t;j <= k;++j){
            scanf("%d",&t);
            if(!(~last[t])){
                add_edge(S,i,cow[t]);
            }else{
                add_edge(last[t],i,INF);
            }
            last[t] = i;
        }
        scanf("%d",&k);
        add_edge(i,T,k);
    }
    printf("%d\n",max_flow(S,T));
    return 0;
}