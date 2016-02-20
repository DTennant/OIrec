#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define MAX_V 500 + 16
int V,match[MAX_V];;                 
vector<int> G[MAX_V];  
bool used[MAX_V];
void init(){for (int i = 0; i < V; ++i){G[i].clear();}}
void add_edge(int u, int v){
	G[u].push_back(v);
	G[v].push_back(u);
}
bool dfs(int v){
	used[v] = true;
	for (vector<int>::iterator it = G[v].begin(); it != G[v].end(); ++it){
		int u = *it, w = match[u];
		if (w < 0 || !used[w] && dfs(w)){
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}
int bipartite_matching(){
	int res = 0;
	memset(match, -1, sizeof(match));
	for (int v = 0; v < V; ++v){
		if (match[v] < 0){
			memset(used, 0, sizeof(used));
			if (dfs(v)){
				++res;
			}
		}
	}
	return res;
}
int main(void){
	while (~scanf("%d", &V)){
		init();
		for (int i = 0,v,m,u; i < V; ++i){
			scanf("%d: (%d)", &v, &m);
			for (int j = 0; j < m; ++j){
				scanf("%d", &u);
				G[v].push_back(u);
			}
		}
		printf("%d\n", V - bipartite_matching());
	}
	return 0;
}