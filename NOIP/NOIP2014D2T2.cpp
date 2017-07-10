#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>
#define MAX_N 10010
#define INF 0x3f3f3f3f
using namespace std;
queue<int> que;
vector<int> G[MAX_N], rG[MAX_N];
int vis[MAX_N], inq[MAX_N], d[MAX_N], ok[MAX_N], N, M, s, t;
inline int spfa (int s, int t) {
	if (!ok[s]) return -1;
	memset(d, INF, sizeof(d));
	inq[s] = true; d[s] = 0;
	que.push(s);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (int i = 0; i < G[u].size(); ++i) {
			int v = G[u][i];
			if (ok[v] && d[v] > d[u] + 1){
				d[v] = d[u] + 1;
				if (!inq[v]) {
					inq[v] = true;
					que.push(v);
				}
			}
		}
	}
	return d[t] == INF ? -1 : d[t];
}
void rdfs (int t) {
	if (vis[t]) return;
	vis[t] = true;
	for (int i = 0; i < rG[t].size(); ++i) rdfs(rG[t][i]);
}
int main() {
	scanf("%d%d", &N, &M);
	for(int i = 0, u, v; i < M; ++i){
		scanf("%d%d", &u, &v);
		if (u == v) continue;
		G[u].push_back(v);rG[v].push_back(u);
	}
	scanf("%d%d", &s, &t);
	rdfs(t); memset(ok, true, sizeof(ok));
	for (int u = 1; u <= N; ++u) {
		if (!vis[u]) {ok[u] = false; continue;}
		for (int i = 0; i < G[u].size(); ++i){
			int v = G[u][i];
			if (!vis[v]) {ok[u] = false; break;}
		}
	}
	printf("%d\n", spfa(s, t));
	return 0;
}