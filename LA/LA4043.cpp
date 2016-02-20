#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MAX_N 150
#define INF ((1 << 30) - 1)
using namespace std;
double W[MAX_N][MAX_N],Lx[MAX_N],Ly[MAX_N],slack[MAX_N];
int match[MAX_N],N;
bool S[MAX_N],T[MAX_N];
bool dfs(int v){
	S[v] = true;
	for(int i = 1;i <= N;++i)if(!T[i]){
		double t = Lx[v] + Ly[i] - W[v][i];
		if(t == 0){
			T[i] = true;
			if(match[i] == -1 || dfs(match[i])){
				match[i] = v;
				return true;
			}
		}else slack[i] = min(slack[i],t);
	}
	return false;
}
void update(void){
	double d = INF;
	for(int i = 1;i <= N;++i)if(!T[i]){
		d = min(d,slack[i]);
	}
	for(int i = 1;i <= N;++i){
		if(S[i])Lx[i] -= d;
		if(T[i])Ly[i] += d;
		else slack[i] -= d;
	}
}
double KM(void){
	memset(match,-1,sizeof(match));
	memset(Ly,0,sizeof(Ly));
	for(int i = 1;i <= N;++i){
		Lx[i] = -INF;
		for(int j = 1;j <= N;++j)Lx[i] = max(Lx[i],W[i][j]);
	}
	for(int v = 1;v <= N;++v){
		for(int i = 1;i <= N;++i)slack[i] = INF;
		while(true){
			memset(S,0,sizeof(S));
			memset(T,0,sizeof(T));
			if(dfs(v))break;else update();
		}
	}
	double res = 0;
	for(int i = 1;i <= N;++i)if(match[i] != -1)res += W[match[i]][i];
	return res;
}
struct point{
	double x,y;
}a[MAX_N],b[MAX_N];
double dist(const point &a,const point &b){return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));}
int main(){
	while(~scanf("%d",&N)){
		for(int i = 1;i <= N;++i)scanf("%lf%lf",&a[i].x,&a[i].y);
		for(int i = 1;i <= N;++i)scanf("%lf%lf",&b[i].x,&b[i].y);
		for(int i = 1;i <= N;++i){
			for(int j = 1;j <= N;++j){
				W[i][j] = -dist(a[i],b[i]);
			}
		}
		KM();
		for(int i = 1;i <= N;++i)printf("%d\n",match[i]);
		putchar('\n');
	}
	return 0;
}