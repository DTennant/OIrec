#include <cstdio>
#include <algorithm>
#define MAX_N 10010
#define INF 0x7ffffff
using namespace std;
int n, m, k, p, l, h;
int inc[MAX_N], dec[MAX_N], lower[MAX_N], upper[MAX_N], dp[MAX_N][1001];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; ++i) scanf("%d%d", &inc[i], &dec[i]);
	for (int i = 1; i <= n; ++i) lower[i] = 0, upper[i] = m + 1; 
	for (int i = 1; i <= k; ++i) {
		scanf("%d%d%d", &p, &l, &h);
		lower[p] = l;
		upper[p] = h;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
			dp[i][j] = INF;
	dp[0][0] = INF;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (j >= inc[i - 1]) {
				dp[i][j] = min(dp[i][j], dp[i - 1][j - inc[i - 1]] + 1);
				dp[i][j] = min(dp[i][j], dp[i][j - inc[i - 1]] + 1);
			}
			if (j == m) {
				for (int k = j - inc[i - 1]; k <= m; k++) {
					dp[i][j] = min(dp[i][j], dp[i - 1][k] + 1);
					dp[i][j] = min(dp[i][j], dp[i][k] + 1);
				}
			}
		}
		for (int j = lower[i] + 1; j <= upper[i] - 1; ++j) {
			if (j + dec[i - 1] <= m) dp[i][j] = min(dp[i][j], dp[i - 1][j + dec[i - 1]]);
		}
		for (int j = 1; j <= lower[i]; ++j) dp[i][j] = INF;
		for (int j = upper[i]; j <= m; ++j) dp[i][j] = INF;
	}
	int cnt = k, ans = INF;
	for (int i = n; i >= 1; i--) {
		for (int j = lower[i] + 1; j <= upper[i] - 1; ++j) {
			if (dp[i][j] < INF) ans = min(ans, dp[i][j]);
		}
		if (ans != INF) break;
		if (upper[i] <= m) cnt--;
	}
	if(cnt == k)printf("1\n%d\n", ans);
	else printf("0\n%d\n", cnt);
	return 0;
}