#include <cstdio>
#include <queue>
#include <algorithm>
#define MAX_N 200010
using namespace std;
int to[MAX_N], vis[MAX_N], deg[MAX_N], n, ans;
queue<int> que;
int main() {
	scanf("%d", &n); ans = n;
	for (int i = 1; i <= n; ++i) { scanf("%d", to + i); ++deg[to[i]]; }
	for (int i = 1; i <= n; ++i) {
		if (deg[i] == 0) {
			que.push(i);
			vis[i] = 1;
		}
	}
	while (!que.empty()) {
		int u = que.front(); que.pop();
		--deg[to[u]];
		if (deg[to[u]] == 0) {
			vis[to[u]] = 1;
			que.push(to[u]);
		}
	}
	for (int i = 1, t, v; i <= n; ++i) {
		if (vis[i] == 0 && deg[i] != 0) {
			vis[i] = 1; t = 1;
			v = to[i];
			while (!vis[v]) { vis[v] = 1; v = to[v]; ++t; }
			ans = min(t, ans);
		}
	}
	printf("%d\n", ans);
	return 0;
}