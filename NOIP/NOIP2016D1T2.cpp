#include <cstdio>
#include <vector>
#include <queue>
#define MAX_N 300010
using namespace std;
int n, m, W[MAX_N], S[MAX_N], T[MAX_N];
vector<int> G[MAX_N];
void bfs();
void minus();
void right();
void add_edge(int u, int v){G[u].push_back(v);G[v].push_back(u);}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0, u, v;i < n - 1;++i){
		scanf("%d%d", &u, &v);
		add_edge(u,v);
	}
	for(int i = 0;i < n;++i)scanf("%d", W + i);
	for(int i = 0;i < m;++i)scanf("%d%d", S + i, T + i);
	if(n <= 1000 && m <= 1000){
		bfs();
	}
	return 0;
}
void bfs(){
	queue<int> que;
	
}