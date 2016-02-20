#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define MAX_N 1010
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
struct Edge{int from, to;ll cap, flow ,cost;};
struct MCMF{
    int n, m, source, sink;
    vector<Edge> edges;
    vector<int> G[MAX_N];
    ll d[MAX_N], f[MAX_N];int p[MAX_N];bool vis[MAX_N];
    void init(int n) {this->n = n;for (int i = 0; i <= n; i++)G[i].clear();edges.clear();}
    void AddEdge(int from, int to, ll cap, ll cost) {
        edges.push_back((Edge){from, to, cap, 0, cost});
        edges.push_back((Edge){to, from, 0, 0, -cost});
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }
    bool BellmanFord(int s, int t, ll &flow, ll &cost) {
        for (int i = 0; i <= n; i++)d[i] = INF;
        memset(vis, 0, sizeof(vis));
        vis[s] = true; d[s] = 0; f[s] = INF; p[s] = 0;
        queue<int> que;que.push(s);
        while (!que.empty()) {
            int v = que.front();que.pop();vis[v] = false;
            for (int i = 0; i < G[v].size(); i++) {
                Edge &e = edges[G[v][i]];
                if (e.cap > e.flow && d[e.to] > d[v] + e.cost) {
                    d[e.to] = d[v] + e.cost;
                    p[e.to] = G[v][i];
                    f[e.to] = min(f[v], e.cap - e.flow);
                    if (!vis[e.to]) {
                        vis[e.to] = true;
                        que.push(e.to);
                    }
                }
            }
        }
        if (d[t] > 0)return false;//important~
        flow += f[t];
        cost += d[t] * f[t];
        int u = t;
        while (u != s) {
            edges[p[u]].flow += f[t];
            edges[p[u] ^ 1].flow -= f[t];
            u = edges[p[u]].from;
        }
        return true;
    }
    ll Mincost(int s, int t) {
        ll flow = 0, cost = 0;
        while (BellmanFord(s, t, flow, cost));
        return cost;
    }
}mcmf;
int N, M, source, sink, T;
struct Node{ll m, n, p, s, e;}node[MAX_N];//m为生产成本，n为最大产量，p为销售单价，s为最大销售量，e为X元素衰变的时间
int main() {
    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        scanf("%d%d", &N, &M);
        source = 0; sink = 2 * N + 1;
        mcmf.init(sink);
        for (int i = 1; i <= N; i++) { 
            scanf("%lld%lld%lld%lld%lld", &node[i].m, &node[i].n, &node[i].p, &node[i].s, &node[i].e);
            mcmf.AddEdge(source, i, node[i].n, 0);
            mcmf.AddEdge(i + N, sink, node[i].s, 0);
        }
        for (int i = 1; i <= N; i++) {
            mcmf.AddEdge(i, i + N, INF, node[i].m - node[i].p);
            for (int j = 1; j <= node[i].e && i + j <= N; j++) 
                mcmf.AddEdge(i, i + j + N, INF, M * j + node[i].m - node[i+j].p);
        }
        printf("Case %d: %lld\n", kase, -mcmf.Mincost(source, sink));
    }
    return 0;
}