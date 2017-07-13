#include <cstdio>
#include <set>
#include <map>
#include <algorithm>
#define INF 5000000000LL
#define MAX_N 100010
#define MAX_LOG_N 17
using namespace std;
typedef long long ll;
const double pi = acos(-1.0);
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
    return x * f;
}
int bin[20], n, x0, m, h[MAX_N], fa[MAX_N], fb[MAX_N], to[MAX_N][MAX_LOG_N];
ll a[MAX_N], b[MAX_N], va[MAX_N][MAX_LOG_N], vb[MAX_N][MAX_LOG_N];
set<ll> q;
map<ll,int> mp;
struct data{
    ll h, key;
    bool operator < (const data &b) const {
        return key < b.key || (key == b.key && h < b.h);
    }
}t[5];
double cal1(int x, int val){
    int t1 = 0, t2 = 0;
    for (int i = 16; i >= 0; i--) {
        if(to[x][i] && t1 + va[x][i] + t2 + vb[x][i] <= val){
            t1 += va[x][i]; t2 += vb[x][i];
            x = to[x][i];
        }
    }
	if(t2 == 0)return INF;
    return (double)t1 / (double)t2;
}
void cal2(int x, int val) {
    int t1 = 0, t2 = 0;
    for(int i = 16; i >= 0; i--) {
        if(to[x][i] && t1 + va[x][i] + t2 + vb[x][i] <= val){
            t1 += va[x][i]; t2 += vb[x][i];
            x = to[x][i];
        }
    }
    printf("%d %d\n",t1,t2);
}
int main() {
    n = read();
    q.insert(-INF); q.insert(INF);
    for(int i = 1; i <= n; i++){
        h[i] = read();
        mp[h[i]] = i;
    }
    for(int i = n; i; i--){
        q.insert(h[i]);
        t[1].h = *--q.lower_bound(h[i]), t[2].h = *q.upper_bound(h[i]);
        if(t[1].h != -INF)t[3].h = *--q.lower_bound(t[1].h);
        else t[3].h = -INF;
        if(t[2].h != INF)t[4].h = *q.upper_bound(t[2].h);
        else t[4].h = INF;
        for(int k = 1; k <= 4; k++)t[k].key = abs(t[k].h - h[i]);
        sort(t + 1,t + 5);
        a[i] = t[2].key; fa[i] = mp[t[2].h];
        b[i] = t[1].key; fb[i] = mp[t[1].h];
        for(int j = 0; j <= 16; j++) {
            if (j == 0) {
                if(fa[i]){va[i][0] = a[i]; to[i][0] = fa[i];}
            } else if(j == 1){
                if(fb[fa[i]]){ va[i][1] = a[i]; vb[i][1] = b[fa[i]]; to[i][1] = fb[fa[i]];}
            }
            else if(to[to[i][j - 1]][j - 1]){
                va[i][j] = va[i][j - 1] + va[to[i][j - 1]][j - 1];
                vb[i][j] = vb[i][j - 1] + vb[to[i][j - 1]][j - 1];
                to[i][j] = to[to[i][j - 1]][j - 1];
            }
            else break;
        }
    }
    double mn = 1e60; int ans = 0;
    x0 = read();
    for(int i = 1; i <= n; i++){
        double t = cal1(i, x0);
        if(t < mn || (t == mn && h[i] > h[ans])){
            mn = t; ans = i;
        }
    }
    printf("%d\n", ans);
    m = read();
    for(int i = 1; i <= m; i++){
        int s = read(), x = read();
        cal2(s, x);
    }
    return 0;
}