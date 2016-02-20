#include <cstdio>
#include <cstring>
#include <algorithm>
#define lson l,m,rt << 1
#define rson m + 1,r,rt << 1 | 1
#define MAX_N 12000
using namespace std;
bool hash[MAX_N];
int left[MAX_N],right[MAX_N],x[MAX_N * 3];
int col[MAX_N << 4],cnt;
void PushDown(int rt){
	if(~col[rt]){
		col[rt << 1] = col[rt << 1 | 1] = col[rt];
		col[rt] = -1;
	}
}
void update(int L,int R,int c,int l,int r,int rt){
	if(L <= l && r <= R){
		col[rt] = c;
		return ;
	}
	PushDown(rt);
	int m = (l + r) >> 1;
	if(L <= m)update(L,R,c,lson);
	if(R > m)update(L,R,c,rson);
}
void query(int l,int r,int rt){
	if(~col[rt]){
		if(!hash[col[rt]])cnt++;
		hash[col[rt]] = true;
		return ;
	}
	if(l == r)return ;
	int m = (l + r) >> 1;
	query(lson);query(rson);
}
int Bin(int key,int n,int x[]){
	int l = 0,r = n - 1;
	while(l <= r){
		int m = (l + r) >> 1;
		if(x[m] == key)return m;
		if(x[m] < key)l = m + 1;
		else r = m - 1;
	}
	return -1;
}