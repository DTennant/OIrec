#include <cstdio>
#define MAX_N 200100
#define lson l,m,rt << 1
#define rson m + 1,r,rt << 1 | 1
using namespace std;
int sum[MAX_N << 2],n,ans[MAX_N << 2],pos[MAX_N],val[MAX_N];
void PushUP(int rt){
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void build(int l,int r,int rt){
	sum[rt] = r - l + 1;
	if(l == r)return ;
	int m = (l + r) >> 1;
	build(lson);build(rson);
}
void update(int pos,int val,int l,int r,int rt){
	if(l == r){
		ans[rt] = val;
		--sum[rt];
		return ;
	}
	int m = (l + r) >> 1;
	if(pos <= sum[rt << 1])update(pos,val,lson);
	else update(pos - sum[rt << 1],val,rson);
	PushUP(rt);
}
void print(int l,int r,int rt){
	if(l == r){printf("%d ",ans[rt]);return ;}
	int m = (l + r) >> 1;
	print(lson);print(rson);
}
int main(){
	while(~scanf("%d",&n)){
		for(int i = 0;i < n;++i)scanf("%d%d",&pos[i],&val[i]);
		build(1,n,1);
		for(int i = n - 1;i >= 0;--i)update(pos[i] + 1,val[i],1,n,1);
		print(1,n,1);putchar('\n');
	}
	return 0;
}