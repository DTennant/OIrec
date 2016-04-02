#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX_N 500100
#define MAX_NODE 400100
#define SIGMA_SIZE 30
using namespace std;
const int mod = 20071027;
char word[MAX_N];
int dp[MAX_N],n;
struct Trie{
	int ch[MAX_NODE][SIGMA_SIZE],val[MAX_NODE],sz;
	void init(){
		sz = 1;
		memset(ch[0],0,sizeof(ch[0]));
		memset(val,0,sizeof(val));
	}
	int idx(char c){return c - 'a';}
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
		val[u] = v;
	}
	void search(char *s,int p,int len){
		int u = 0;
		for(int i = 0;i < len;++i){
			int c = idx(s[i]);
			if(!ch[u][c])return ;
			u = ch[u][c];
			if(val[u])dp[p] = (dp[p] + dp[p + val[u]]) % mod;
		}
	}
}solver;
int main(){
	for(int kase = 1;~scanf("%s",word);++kase){
		scanf("%d",&n);
		solver.init();
		int len = strlen(word);
		dp[len] = 1;
		char tmp[100];
		for(int i = 0;i < n;++i){
			scanf("%s",tmp);
			solver.insert(tmp,strlen(tmp));
		}
		for(int i = len - 1;i >= 0;--i){
			dp[i] = 0;
			solver.search(word + i,i,len - i);
		}
		printf("Case %d: %d\n",kase,dp[0]);
	}
	return 0;
}