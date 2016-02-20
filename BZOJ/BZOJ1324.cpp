#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define MAX_N 1010
#define INF 0x3f3f3f3f
using namespace std;
struct edge{int to,cap,rev;};
vector<edge> G[MAX_N];
queue<int> que;
const int dx[] = {0,1,0,-1,0};
const int dy[] = {0,0,1,0,-1};
int level[MAX_N],iter[MAX_N];
int input[MAX_N][MAX_N],num[MAX_N][MAX_N],sum,N,M;
inline int read(){
    int x = 0,f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
    return x * f;
}
inline bool inmap(int x,int y){return x && y && x <= N && y <= M;}
inline void init(){for(int i = 0;i < MAX_N;++i)G[i].clear();}
inline void add_edge(int from,int to,int cap){
    G[from].push_back((edge){to,cap,G[to].size()});
    G[to].push_back((edge){from,0,G[from].size() - 1});
}
inline int bfs(int s){
    memset(level,-1,sizeof(level));
    que.push(s);level[s] = 0;
    while(!que.empty()){
        int v = que.front();que.pop();
        for(int i = 0;i < G[v].size();++i){
            edge e = G[v][i];
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
        if(e.cap > 0 && level[v] < level[e.to]){
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
int max_flow(int s,int t){
    int flow = 0;
    for(;;){
        bfs(s);
        if(level[t] < 0)return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while((f = dfs(s,t,INF)) > 0){
            flow += f;
        }
    }
}
int main(){
    N = read(),M = read();
    static int S = 0;
    static int T = N * M + 1;
    static int cnt = 0;
    init();
    for(int i = 1;i <= N;++i){
        for(int j = 1;j <= M;++j){
            scanf("%d",&input[i][j]);
            sum += input[i][j];
            num[i][j] = ++cnt;
            if((i + j) & 1)
                add_edge(S,num[i][j],input[i][j]);
            else
                add_edge(num[i][j],T,input[i][j]);
        }
    }
    for(int i = 1;i <= N;++i){
        for(int j = 1;j <= M;++j){
            if(((i + j) & 1) == 0)continue;
            for(int k = 1;k <= 4;++k){
                int nx = i + dx[k],ny = j + dy[k];
                if(inmap(nx,ny))add_edge(num[i][j],num[nx][ny],INF);
            }
        }
    }
    printf("%d\n",sum - max_flow(S,T));
    return 0;
}