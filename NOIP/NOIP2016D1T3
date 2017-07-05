#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX_N 2010
#define MAX_M 2010
#define MAX_V 310
using namespace std;
int n, m, v, e;
int G[MAX_V][MAX_V], d[MAX_V], c[MAX_V];
double p[MAX_V], dp[MAX_N][MAX_M][2];
void floyd(){
	for(int i = 0;i < v;++i){
		for(int j = 0;j < v;++j){
			for(int k = 0;k < v;++k){
				G[i][j] = min(G[i][j],G[i][k] + G[k][j]);
			}
		}
	}
}
int main(){
	scanf("%d%d%d%d", &n, &m, &v, &e);
	for(int i = 0;i < n;++i){scanf("%d", c + i);--c[i];}
	for(int i = 0;i < n;++i){scanf("%d", d + i);--d[i];}
	for(int i = 0;i < n;++i)scanf("%lf", p + i);
	memset(G, 0x3f, sizeof(G));
	for(int i = 0, f, t, c;i < n;++i){
		scanf("%d%d%d", &f, &t, &c);--f;--t;
		G[f][t] = G[t][f] = min(G[f][t], c);
	}
	for(int i = 0;i < n;++i)G[i][i] = 0;
	floyd();
	
	return 0;
}