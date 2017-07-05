#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX_N = 300010;
const int MAX_M = 600010; 
int n, m, ecnt, first[MAX_N], next[MAX_M], to[MAX_M];
int deep[MAX_N], ans[MAX_N], val[MAX_N], sta[MAX_N], MAX_D, w[MAX_N];
int head[MAX_N], tt[MAX_M], nn[MAX_M], f[MAX_N], vis[MAX_N], num[1000011];
vector<int> vec[MAX_N], vec2[MAX_N], vec3[MAX_N];
struct node{int s, t, lca, len;}a[MAX_N];
inline void link(int x, int y){ next[++ecnt] = first[x]; first[x] = ecnt; to[ecnt] = y; }
inline void link2(int x, int y){ nn[++ecnt] = head[x]; head[x] = ecnt; tt[ecnt] = y; }
int find(int x){ if(f[x] != x) f[x] = find(f[x]); return f[x]; }
void tarjan(int x, int fa){ 
    f[x] = x; vis[x] = true;
    for(int i = head[x];i;i = nn[i]) {
        int v = tt[i];
        if(x == a[v].s && vis[a[v].t]) a[v].lca = find(a[v].t);
        if(x == a[v].t && vis[a[v].s]) a[v].lca = find(a[v].s);
    }
    for(int i = first[x];i;i = next[i]) {
        int v = to[i]; 
        if(v == fa) continue; 
        deep[v] = deep[x] + 1; 
        tarjan(v,x); 
        f[v] = x;
    }
}
void dfs(int x, int fa){
    int now = w[x] + deep[x], sav; 
    if(now <= MAX_D) sav = sta[now];
    for(int i = first[x];i;i = next[i]) {
        int v = to[i]; 
        if(v == fa) continue;
        dfs(v, x);
    }
    sta[deep[x]] += val[x]; 
    if(now <= MAX_D) ans[x] = sta[now] - sav;
    for(int i = 0;i < vec[x].size();i++) sta[deep[vec[x][i]]]--;
}
void dfs2(int x, int fa){
    int now = deep[x] - w[x] + 300000, sav; 
    sav = num[now];
    for(int i = first[x];i;i = next[i]) {
        int v = to[i]; 
        if(v == fa) continue;
        dfs2(v, x);
    }
    for(int i = 0;i < vec2[x].size();i++) num[300000 + vec2[x][i]]++;
    ans[x] += num[now] - sav;
    for(int i=0;i < vec3[x].size();i++) num[300000 + vec3[x][i]]--;
}
int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1, x, y;i < n;i++) {
        scanf("%d%d", &x, &y);
        link(x, y);link(y, x); 
    }
    for(int i = 1;i <= n;i++)scanf("%d", w + i);
    ecnt = 0;
    for(int i = 1;i <= m;i++) { 
        scanf("%d%d", &a[i].s, &a[i].t);
        val[a[i].s]++; 
        link2(a[i].s, i);link2(a[i].t, i);
    }
    deep[1] = 1; 
    tarjan(1, 0);
    for(int i = 1;i <= n;i++) MAX_D = max(MAX_D, deep[i]);
    for(int i = 1;i <= m;i++) {
        a[i].len = deep[a[i].s] + deep[a[i].t] - deep[a[i].lca] * 2;
        vec[a[i].lca].push_back(a[i].s);
    }
    dfs(1, 0); 
    for(int i = 1;i <= m;i++) {
        vec2[a[i].t].push_back(deep[a[i].t] - a[i].len);
        vec3[a[i].lca].push_back(deep[a[i].t] - a[i].len);
    }
    dfs2(1, 0);
    for(int i = 1;i <= m;i++) if(deep[a[i].s] - deep[a[i].lca] == w[a[i].lca]) ans[a[i].lca]--;
    for(int i = 1;i <= n;i++) printf("%d%c", ans[i], i == n ? '\n' : ' '); 
    return 0;
}