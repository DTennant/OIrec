#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAX_N 521
using namespace std;
vector<int> G[MAX_N];
int V,status[MAX_N],lowlink[MAX_N],index[MAX_N],root;
bool is_cut_vertex[MAX_N],has_cut_vertex;
void init(const int &v){
    V = v;
    has_cut_vertex = false;
    for(int i = 0;i <= V;++i)G[i].clear();
}
void tarjan_dfs(int current,int from,int depth){
    status[current] = 1;
    lowlink[current] = index[current] = depth;
    int sub_tree = 0,v;
    for(vector<int>::const_iterator it = G[current].begin(),end = G[current].end();it != end;++it){
        v = *it;
        if(v != from && status[v] == 1){
            lowlink[current] = min(lowlink[current],index[v]);
        }
        if(status[v] == 0){
            tarjan_dfs(v,current,depth + 1);
            ++sub_tree;
            lowlink[current] = min(lowlink[current],lowlink[v]);
            if((current == root && sub_tree > 1) || (current != root && lowlink[v] >= index[current])){
                is_cut_vertex[current] = true;
                has_cut_vertex = true;
            }
        }
    }
    status[current] = 2;
}
void calc(int del){
    memset(is_cut_vertex,false,sizeof(is_cut_vertex));
    memset(status,0,sizeof(status));
    memset(lowlink,0,sizeof(lowlink));
    memset(index,0,sizeof(index));
    status[del] = 2;
    root = del == 0 ? 1 : 0;
    tarjan_dfs(root,-1,1);
}
bool solve(){
	for(int i = 0;i < V;++i){
		calc(i);
		for(int j = 0;j < V;++j){
			if(status[j] == 0){
				has_cut_vertex = true;
				break;
			}
		}
		if(has_cut_vertex)break;
	}
	return !has_cut_vertex;
}
int main(){
	int N,M;
	while(scanf("%d%d",&N,&M),N + M){
		init(N);
		for(int _ = 0,from,to;_ < M;++_){
			scanf("%d%d",&from,&to);
			G[from].push_back(to);
			G[to].push_back(from);
		}
		puts(solve() ? "YES" : "NO");
	}
	return 0;
}
