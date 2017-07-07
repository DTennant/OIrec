#include <cstdio>
int n, map[200][200];
int main() {
    scanf("%d",&n);
    int x = 1, y = (n + 1) / 2;
    map[x][y] = 1;
    for (int i = 2; i <= n * n; i++) {
        if (x == 1 && y != n) x = n, y++;
        else if (x != 1 && y == n) x--, y = 1;
        else if (x == 1 && y == n) x++;
        else if (!map[x - 1][y + 1]) x--, y++;
        else x++;
        map[x][y] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%d%c", map[i][j], j == n ? '\n' : ' ');
    }
    return 0;
}