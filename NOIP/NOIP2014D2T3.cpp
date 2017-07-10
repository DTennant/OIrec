#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;
const int p[] = {20011, 20021, 20023, 20029, 20047};
const int MAX_N = 210;
const int P_N = 5;
int a[P_N][MAX_N], f[P_N][23000], N, M;
int ans[1000010], n = 0;
inline void read(int x) {
	bool flag = true;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') flag = false;
	static int ret[P_N];
	for (int i = 0; i < P_N; i++) ret[i] = 0;
	for (; isdigit(c); c = getchar())
		for (int i = 0; i < P_N; i++)
			ret[i] = (ret[i] * 10 + c - '0') % p[i];
	for (int i = 0; i < P_N; i++) a[i][x] = flag ? ret[i] : p[i] - ret[i];
}
int calculate(int x, int y) {
	int res = 0;
	for (int i = N; i; i--) res = (res + a[x][i]) * y % p[x];
	if ((res += a[x][0]) >= p[x]) res -= p[x];
	return res;
}
int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i <= N; i++) read(i);
	for (int i = 0; i < P_N; i++)
		for (int j = 0; j < p[i]; j++)
			f[i][j] = calculate(i, j);
	for (int i = 1; i <= M; i++) {
		bool t = true;
		for (int j = 0; j < P_N; j++) if (f[j][i % p[j]]) t = false;
		if (t) ans[n++] = i;
	}
	printf("%d\n", n);
	for (int i = 0; i < n; i++) printf("%d\n", ans[i]);     
	return 0;
}