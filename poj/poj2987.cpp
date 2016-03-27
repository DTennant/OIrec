#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f3f3f3f3f
#define MAX_N 5500
using namespace std;
typedef long long ll;
struct edge{int to;ll cap;int rev;};
vector<edge> G[MAX_N];
queue<int> que;
int level[MAX_N],iter[MAX_N],N,M,C[MAX_N];
inline void add_edge(int from,int to,ll cap){
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
ll dfs(int v,int t,ll f){
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
ll max_flow(int s,int t){
    ll flow = 0;
    for(;;){
        memset(iter,0,sizeof(iter));
        bfs(s);
        if(level[t] < 0)return flow;
        ll f;
        while((f = dfs(s,t,INF)) > 0){
            flow += f;
        }
    }
}
int counted,visited[MAX_N];
void solve(int v){
    ++counted;
    visited[v] = true;
    for(int i = 0;i < G[v].size();++i){
        const edge &e = G[v][i];
        if(e.cap > 0 && !visited[e.to]){
            solve(e.to);
        }
    }
}
int main(){
    scanf("%d%d",&N,&M);static const int S = 0,T = N + 1;
    ll sum = 0;
    for(int i = 1;i <= N;++i)scanf("%d",&C[i]);
    for(int i = 1,a,b;i <= M;++i){
        scanf("%d%d",&a,&b);
        add_edge(a,b,INF);
    }
    for(int i = 1;i <= N;++i){
        if(C[i] > 0){
            add_edge(S,i,C[i]);sum += C[i];
        }else{
            add_edge(i,T,-C[i]);
        }
    }
    ll max_profit = sum - max_flow(S,T);
    solve(S);
    printf("%d %I64d\n",--counted,max_profit);
    return 0;
}