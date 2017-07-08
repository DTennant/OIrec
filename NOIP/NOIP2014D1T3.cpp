#include <cstdio>
#include <algorithm>
#define MAX_N  10010
using namespace std;
const int INF = 0x7ffffff;
int n, m, k, p, l, h;
int x[MAX_N], y[MAX_N], down[MAX_N], up[MAX_N], dp[MAX_N][1001];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
	for (int i = 1; i <= n; ++i) down[i] = 0, up[i] = m + 1; 
	for (int i = 1; i <= k; ++i) {
		scanf("%d%d%d", &p, &l, &h);
		down[p] = l;
		up[p] = h;
	}
	for (int i = 1; i <= n; ++i)
	    for (int j = 0; j <= m; ++j)
	             dp[i][j] = INF;
	dp[0][0] = INF;
	int arrive = k;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (j >= x[i - 1]) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j - x[i - 1]] + 1);
				dp[i][j] = min(dp[i][j], dp[i][j - x[i - 1]] + 1);
			}
			if (j == m) {
				for (int k = j - x[i - 1]; k <= m; k++) {
					dp[i][j] = min(dp[i][j], dp[i - 1][k] + 1);
					dp[i][j] = min(dp[i][j], dp[i][k] + 1);
				}
			}
		}
		for (int j = down[i] + 1; j <= up[i] - 1; ++j) {
			if( j + y[i - 1] <= m) dp[i][j] = min(dp[i][j], dp[i - 1][j + y[i - 1]]);
		}
		for (int j = 1; j <= down[i]; ++j) dp[i][j] = INF;
		for (int j = up[i]; j <= m; ++j) dp[i][j] = INF;
	}
	int cnt = k, ans = INF;
	for (int i = n; i >= 1; i--) {
		for (int j = down[i] + 1; j <= up[i] - 1; ++j) {
			if (dp[i][j] < INF) ans = min(ans, dp[i][j]);
		}
		if (ans != INF) break;
		if (up[i] <= m) cnt--;
	}
	if(cnt == k)printf("1\n%d\n", ans);
	else printf("0\n%d\n", cnt);
	return 0;
}