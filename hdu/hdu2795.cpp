#include <cstdio>
#include <algorithm>
#define MAX_N 200100
#define lson l,m,rt << 1
#define rson m + 1,r,rt << 1 | 1
using namespace std;
int MAX[MAX_N << 2],n,h,w;
void PushUP(int rt){
	MAX[rt] = max(MAX[rt << 1],MAX[rt << 1 | 1]);
}
void build(int l,int r,int rt){
	MAX[rt] = w;
	if(l == r)return;
	int m = (l + r) >> 1;
	build(lson);build(rson);
}
int query(int x,int l,int r,int rt){
	if(l == r){
		MAX[rt] -= x;
		return l;
	}
	int m = (l + r) >> 1;
	int ret = (MAX[rt << 1] >= x) ? query(x,lson) : query(x,rson);
	PushUP(rt);
	return ret;
}
int main(){
	while(~scanf("%d%d%d",&h,&w,&n)){
		h = min(h,n);
		build(1,h,1);
		for(int i = 0,x;i < n;++i){
			scanf("%d",&x);
			if(MAX[1] < x)puts("-1");
			else printf("%d\n",query(x,1,h,1));
		}
	}
	return 0;
}