#include <cmath>
#include <cstring>
#include <iostream>
#define MAX_N 200
using namespace std;
int S,V;
struct Point{
	double x,y;
	double dist(const Point &rhs) const {
		return sqrt((x - rhs.x)*(x - rhs.x) + (y - rhs.y)*(y - rhs.y));
	}
	bool connected(const Point &rhs) const {
		return this->dist(rhs) <= (double)(S * V);
	}
}gopher[MAX_N],hole[MAX_N];
int match[MAX_N],N,M;
bool used[MAX_N],G[MAX_N][MAX_N];
bool dfs(int v){
	for(int i = 1;i <= M;++i){
		if(!used[i] && G[v][i]){
			used[i] = true;
			if(match[i] == -1 || dfs(match[i])){
				match[i] = v;
				return true;
			}
		}
	}
	return false;
}
int bipartite_matching(){
	int ans = 0;
	memset(match,-1,sizeof(match));
	for(int i = 1;i <= N;++i){
		memset(used,false,sizeof(used));
		if(dfs(i))++ans;
	}
	return ans;
}
int main(){
	while(cin >> N >> M >> S >> V){
		for(int i = 1;i <= N;++i)cin >> gopher[i].x >> gopher[i].y;
		for(int i = 1;i <= M;++i)cin >> hole[i].x >> hole[i].y;
		for(int i = 1;i <= N;++i){
			for(int j = 1;j <= M;++j){
				G[i][j] = gopher[i].connected(hole[j]);
			}
		}
		cout << N - bipartite_matching() << endl;
	}
	return 0;
}