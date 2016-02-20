#include <cstdio>
#define lson l,m,rt << 1
#define rson m + 1,r,rt << 1 | 1
#define MAX_N 120000
typedef long long ll;
ll sum[MAX_N << 2],add[MAX_N << 2];
int n,q;
void PushUp(int rt){
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void PushDown(int rt,int m){
	if(add[rt]){
		add[rt << 1] += add[rt];
		add[rt << 1 | 1] += add[rt];
		sum[rt << 1] += add[rt] * (m - (m >> 1));
		sum[rt << 1 | 1] += add[rt] * (m >> 1);
		add[rt] = 0;
	}
}
void build(int l,int r,int rt){
	add[rt] = 0;
	if(l == r){
		scanf("%lld",&sum[rt]);
		return ;
	}
	int m = (l + r) >> 1;
	build(lson);build(rson);
	PushUp(rt);
}
void update(int L,int R,int c,int l,int r,int rt){
	if(L <= l && r <= R){
		add[rt] += c;
		sum[rt] += c * (r - l + 1);
		return ;
	}
	PushDown(rt,r - l + 1);
	int m = (l + r) >> 1;
	if(L <= m)update(L,R,c,lson);
	if(R > m)update(L,R,c,rson);
	PushUp(rt);
}
ll query(int L,int R,int l,int r,int rt){
	if(L <= l && r <= R){
		return sum[rt];
	}
	PushDown(rt,r - l + 1);
	int m = (l + r) >> 1;
	ll ret = 0;
	if(L <= m)ret += query(L,R,lson);
	if(R > m)ret += query(L,R,rson);
	return ret;
}
int main(){
	scanf("%d%d",&n,&q);
	build(1,n,1);
	for(int a,b,c;q--;){
		char op[2];
		scanf("%s",op);
		if(op[0] == 'C'){
			scanf("%d%d%d",&a,&b,&c);
			update(a,b,c,1,n,1);
		}else{
			scanf("%d%d",&a,&b);
			printf("%lld\n",query(a,b,1,n,1));
		}
	}
	return 0;
}