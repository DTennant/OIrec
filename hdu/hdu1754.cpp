#include <cstdio>
#include <algorithm>
#define MAX_N 300000
#define lson l,m,rt << 1
#define rson m + 1,r,rt << 1 | 1
using namespace std;
int ans[MAX_N << 2],N,M;
void PushUP(int rt){
	ans[rt] = max(ans[rt << 1],ans[rt << 1 | 1]);
}
void build(int l,int r,int rt){
	if(l == r){
		scanf("%d",&ans[rt]);
		return ;
	}
	int m = (l + r) >> 1;
	build(lson);build(rson);
	PushUP(rt);
}
void update(int p,int sc,int l,int r,int rt){
	if(l == r){
		ans[rt] = sc;
		return ;
	}
	int m = (l + r) >> 1;
	if(p <= m)update(p,sc,lson);
	else update(p,sc,rson);
	PushUP(rt);
}
int query(int L,int R,int l,int r,int rt){
	if(L <= l && r <= R){
		return ans[rt];
	}
	int m = (l + r) >> 1;
	int ret = -1;
	if(L <= m)ret = max(ret,query(L,R,lson));
	if(R > m)ret = max(ret,query(L,R,rson));
	return ret;
}
int main(){
	while(~scanf("%d%d",&N,&M)){
		build(1,N,1);
		char op[2];
		for(int a,b;M--;){
			scanf("%s%d%d",op,&a,&b);
			if(op[0] == 'Q')printf("%d\n",query(a,b,1,N,1));
			else update(a,b,1,N,1);
		}
	}
	return 0;
}