#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAX_N 300011
#define MAX_M 600011
using namespace std;
int n, m, ecnt, first[MAX_N], next[MAX_M], to[MAX_M], f[MAX_N][20];
int deep[MAX_N], ans[MAX_N], val[MAX_N], sta[MAX_N], MAX_D;
int w[MAX_N], num[1000011];
int head[MAX_N], tt[MAX_M], nn[MAX_M], father[MAX_N], vis[MAX_N];
vector<int> 
inline int get_int(){
    int w = 0,q = 0;char c = getchar();while((c < '0' || c > '9') && c != '-')c = getchar();
    if(c == '-')q = 1, c = getchar();while(c >= '0' && c <= '9')w = w * 10 + c - '0', c = getchar();return q ? -w : w;
}
