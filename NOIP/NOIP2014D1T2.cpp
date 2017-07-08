#include <cstdio>
#include <vector>
#include <algorithm>
#define MOD 10007
#define MAX_N 200005
#define ll long long
using namespace std;
int n;
ll w[MAX_N],mx[MAX_N],sum[MAX_N], ans1[MAX_N],ans2[MAX_N];
vector<int> e[MAX_N];
void dp (int u, int fa) {
	for(int i = 0; i < e[u].size(); i++){
		int v = e[u][i];
		if (v == fa) continue;
		dp(v, u);
		mx[u] = max(mx[u], w[v]);
		sum[u] = (sum[u] + w[v]) % MOD;
		ans1[u] = max(ans1[u], w[u] * mx[v]);
		ans1[u] = max(ans1[u], ans1[v]);
		ans2[u] = (ans2[u] + w[u] * sum[v]) % MOD;
		ans2[u] = (ans2[u] + ans2[v]) % MOD;
	}
	ll t1 = 0, t2 = 0;
	for (int i = 0; i < e[u].size(); i++){
		int v = e[u][i];
		if (v == fa) continue;
		ans1[u] = max(ans1[u], t1 * w[v]);
		ans2[u] = (ans2[u] + t2 * w[v]) % MOD;
		t1 = max(t1, w[v]);
		t2 = (t2 + w[v]) % MOD;
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1, u, v; i < n; i++){
		scanf("%d%d",&u,&v);
		e[u].push_back(v); e[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", w + i);
		w[i] %= MOD;
	}
	dp(1, 0); 
	printf("%d %d\n", ans1[1], ans2[1] * 2 % MOD);
	return 0;
}