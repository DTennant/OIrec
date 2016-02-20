#include <cstdio>
#define lson l,m,rt << 1
#define rson m + 1,r,rt << 1 | 1
#define MAX_N 60000
int sum[MAX_N << 2],T,n;
void PushUP(int rt){
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void build(int l,int r,int rt){
	if(l == r){
		scanf("%d",&sum[rt]);
		return;
	}
	int m = (l + r) >> 1;
	build(lson);build(rson);
	PushUP(rt);
}
void update(int p,int add,int l,int r,int rt){
	if(l == r){
		sum[rt] += add;
		return;
	}
	int m = (l + r) >> 1;
	if(p <= m)update(p,add,lson);
	else update(p,add,rson);
	PushUP(rt);
}
int query(int L,int R,int l,int r,int rt){
	if(L <= l && r <= R){
		return sum[rt];
	}
	int m = (l + r) >> 1;
	int ret = 0;
	if(L <= m)ret += query(L,R,lson);
	if(R > m)ret += query(L,R,rson);
	return ret;
}
int main(){
	scanf("%d",&T);
	for(int kase = 1;kase <= T;++kase){
		printf("Case %d:\n",kase);
		scanf("%d",&n);
		build(1,n,1);
		char op[10];
		for(int a,b;scanf("%s",op);){
			if(op[0] == 'E')break;
			scanf("%d%d",&a,&b);
			if(op[0] == 'Q')printf("%d\n",query(a,b,1,n,1));
			else if(op[0] == 'S')update(a,-b,1,n,1);
			else update(a,b,1,n,1);
		}
	}
	return 0;
}