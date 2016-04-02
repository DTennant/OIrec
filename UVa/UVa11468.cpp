#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAX_NODE 500
#define SIGMA_SIZE 65
using namespace std;
struct AhoCorasickAutomata{
	int ch[MAX_NODE][SIGMA_SIZE],val[MAX_NODE],sz,last[MAX_NODE],f[MAX_NODE],cnt[MAX_NODE];
	void init(){sz = 1;memset(ch[0],0,sizeof(ch[0]));memset(val,0,sizeof(val));memset(cnt,0,sizeof(cnt));}
	int idx(char c){
		if(c >= '0' && c <= '9')return c - '0';
    	else if(c>='A'&&c<='Z')return c - 'A' + 10;
    	else if(c >= 'a' && c <= 'z')return c - 'a' + 36;
	}
	void insert(char *s,int v){
		int u = 0,n = strlen(s);
		for(int i = 0;i < n;++i){
			int c = idx(s[i]);
			if(!ch[u][c]){
				memset(ch[sz],0,sizeof(ch[sz]));
				val[sz] = 0;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u] = 1;
	}
	void print(int j){
		if(j){
			cnt[val[j]]++;
			print(last[j]);
		}
	}
	void find(char *T){
		int n = strlen(T);
		int j = 0;
		for(int i = 0;i < n;++i){
			int c = idx(T[i]);
			j = ch[j][c];
			if(val[j])print(j);
			else if(last[j])print(last[j]);
		}
	}
	int getFail(){
		queue<int> que;
		f[0] = 0;
		for(int c = 0;c < SIGMA_SIZE;++c){
			int u = ch[0][c];
			if(u){que.push(u);f[u] = last[u] = 0;}
		}
		while(!que.empty()){
			int r = que.front();que.pop();
			for(int c = 0;c < SIGMA_SIZE;++c){
				int u = ch[r][c];
				if(!u){ch[r][c] = ch[f[r]][c];continue;}
				que.push(u);
				int v = f[r];
				while(v && !ch[v][c])v = f[v];
				f[u] = ch[v][c];
				last[u] = val[f[u]] ? f[u] : last[f[u]];
				val[u] |= val[f[u]];
			}
		}
	}
}ac;
int L;
double d[MAX_NODE][105];bool vis[MAX_NODE][105];
double prob[65];
double getProb(int u,int L){
	if(!L)return 1.0;
	if(vis[u][L])return d[u][L];
	vis[u][L] = 1;
	double &ans = d[u][L];
	ans = 0.0;
	for(int i = 0;i < SIGMA_SIZE;++i){
		if(!ac.val[ac.ch[u][i]])ans += prob[i] * getProb(ac.ch[u][i],L - 1);
	}
	return ans;
}
int main(){
	int T;
	scanf("%d",&T);
	int kase = 0;
	while(T--){
		char str[40];
		int k;
		scanf("%d",&k);
		ac.init();
		for(int i = 1;i <= k;++i){
			scanf("%s",str);
			ac.insert(str,i);
		}
		ac.getFail();
		memset(vis,0,sizeof(vis));
		scanf("%d",&k);
		double a;
		for(int i = 0;i <= 64;++i)prob[i] = 0;
		for(int i = 1;i <= k;++i){
			scanf("%s%lf",str,&a);
			prob[ac.idx(str[0])] = a;
		}
		int L;
		scanf("%d",&L);
		printf("Case #%d: %.6lf\n",++kase,getProb(0,L));
	}
	return 0;
}