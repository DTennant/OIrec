#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAX_N = 100010, MAX_M = 7000010;
int n, m, q, u, v, t, a[MAX_N];
int s[3][MAX_M], l[3], r[3];
inline int readInt() {
    static int n, ch;
    n = 0, ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) n = n * 10 + ch - '0', ch = getchar();
    return n;
}
inline int getMax() {
    static int now, id;
    now = INT_MIN, id = 0;
    for (int i = 0; i < 3; ++i)
        if (r[i] - l[i] >= 1 && s[i][l[i]] > now)
            now = s[id = i][l[i]];
    return id;
}
int main() {
    n = readInt(), m = readInt(), q = readInt(), u = readInt(), v = readInt(), t = readInt();
    for (int i = 0; i < n; ++i) a[i] = readInt();
    sort(a, a + n), reverse(a, a + n);
    memcpy(s[0], a, sizeof a);
    memset(l, 0, sizeof l);
    memset(r, 0, sizeof r);
    r[0] = n;
    bool flag = false;
    for (int ti = 0, now, id, le, ri, tmp; ti < m; ++ti) {
        id = getMax(), now = s[id][l[id]++];
        tmp = ti * q;
        if ((ti + 1) % t == 0) {
            if (flag) putchar(' ');
            else flag = true;
            printf("%d", now + tmp);
        }
        le = (ll)(now + tmp) * u / v, ri = (now + tmp) - le;
        le -= tmp, ri -= tmp;
        s[1][r[1]++] = le - q, s[2][r[2]++] = ri - q;
    }
    putchar('\n');    
    flag = false;
    int tt = m * q;
    for (int i = 0, id, now; i < n + m; ++i) {
        id = getMax(), now = s[id][l[id]++];
        if ((i + 1) % t == 0) {
            if (flag) putchar(' ');
            else flag = true;
            printf("%d", now + tt);
        }
    }
    putchar('\n');    
    return 0;
}