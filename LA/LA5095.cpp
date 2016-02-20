#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define MAX_N 1010
#define INF 0x3f3f3f3f
using namespace std;
struct Edge{int from, to, cap, flow ,cost;};
struct MCMF{
    int n, m, source, sink, flow, cost;
    vector<Edge> edges;
    vector<int> G[MAX_N];
    int d[MAX_N], f[MAX_N], p[MAX_N];bool vis[MAX_N];
    void init(int n) {this->n = n;for (int i = 0; i <= n; i++)G[i].clear();edges.clear();}
    void AddEdge(int from, int to, int cap, int cost) {
        edges.push_back((Edge){from, to, cap, 0, cost});
        edges.push_back((Edge){to, from, 0, 0, -cost});
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }
    bool BellmanFord(int s, int t, int &flow, int &cost, int need) {
        for (int i = 0; i <= n; i++)d[i] = INF;
        memset(vis, 0, sizeof(vis));
        vis[s] = true; d[s] = 0; f[s] = need; p[s] = 0;
        queue<int> que;
        que.push(s);
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
        if (d[t] == INF)return false;
        flow += f[t];cost += d[t];
        int u = t;
        while (u != s) {
            edges[p[u]].flow += f[t];
            edges[p[u] ^ 1].flow -= f[t];
            u = edges[p[u]].from;
        }
        return true;
    }
    void Mincost(int s, int t, int need) {
        flow = 0, cost = 0;
        while (BellmanFord(s, t, flow, cost, need - flow)) {
            if (need == flow) break;
        }
    }
}mcmf;
int N, M, K, num[6] = {0, 1, 3, 5, 7, 9};
int main() {
    while (~scanf("%d%d%d", &N, &M, &K)){
        mcmf.init(N);
        for (int i = 0, u, v, a, c; i < M; i++) {
            scanf("%d%d%d%d", &u, &v, &a, &c);
            for (int j = 1; j <= c; j++) mcmf.AddEdge(u, v, 1, num[j] * a);
        }
        mcmf.Mincost(1, N, K);
        if (mcmf.flow == K) printf("%d\n", mcmf.cost);
        else puts("-1");
    }
    return 0;
}