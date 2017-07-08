#include <cstdio>
using namespace std;
int n, na, nb, ans1, ans2, a[205], b[205];
int c[5][5] = {
	{ 0,  0,  1, 1,  0},
	{-1,  0,  0, 1,  0},
	{-1, -1,  0,  0, 1},
	{-1, -1, -1,  0, 1},
	{-1, -1, -1, -1, 0},
};
int call(int x, int y) {
	if (x > y) return c[y][x] ^ 1;
	else return c[x][y];
}
int main() {
	scanf("%d%d%d", &n, &na, &nb);
	for (int i = 1; i <= na; i++) scanf("%d", a + i);
	for (int i = 1; i <= nb; i++) scanf("%d", b + i);
	for (int i = 1; i <= n; i++) {
		int x = a[(i - 1) % na + 1], y = b[(i - 1) % nb + 1];
		ans1 += call(x, y);
		ans2 += call(y, x);
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
}