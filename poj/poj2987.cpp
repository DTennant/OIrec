#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define MAX_N 5500
#define MAX_M 65000
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
struct edge{int to;ll cap;int rev;};
vector<edge> G[MAX_N];
queue<int> que;
int level[MAX_N],iter[MAX_N],N,M,B[MAX_N];
void init(){for(int i = 0;i < MAX_N;++i)G[i].clear();}
void add_edge(int from,int to,ll cap){
    G[from].push_back((edge){to,cap,G[to].size()});
    G[to].push_back((edge){from,0,G[from].size() - 1});
}
void bfs(int s){
    memset(level,-1,sizeof(level));
    level[s] = 0;que.push(s);
    while(!que.empty()){
        int v = que.front();que.pop();
        for(int i = 0;i < G[v].size();++i){
            edge &e = G[v][i];
            if(e.cap > 0 && level[e.to] < 0){
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}
ll dfs(int v,int t,ll f){
    if(v == t)return f;
    for(int &i = iter[v];i < G[v].size();++i){
        edge &e = G[v][i];
        if(e.cap > 0 && level[e.to] > level[v]){
            int d = dfs(e.to,t,min(f,e.cap));
            if(d > 0){
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
ll max_flow(int s,int t){
    int flow = 0;
    for(;;){
        bfs(s);
        if(level[t] < 0)return flow;
        int f;
        while((f = dfs(s,t,INF)) > 0){
            flow += f;
        }
    }
}