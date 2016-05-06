#include <cstdio>
#include <algorithm>
#define MAX_N 100100
#define lowbit(i) ((i) & (-(i)))
class bit{
	int c[MAX_N << 1],n;
public:
	bit(int n):n(n){}
	void add(int x,int z){for(;x <= n;x += lowbit(x))c[x] += z;}
	int sum(int x){
		int res = 0;
		for(;x;x -= lowbit(x))res += c[x];
		return res;
	}
};
class bit_max{
	int c[MAX_N << 1],n;
public:
	bit_max(int n):n(n){}
	void add(int x,int z){for(;x <= n;x += lowbit(x))c[x] = std::max(c[x],z);}
	int ask_max(int x){
		int res = -1;
		for(;x;x -= lowbit(x))res = std::max(res,c[x]);
		return res;
	}
};
int a[MAX_N],f[MAX_N],pos[MAX_N];
int main(){
	static int n;
	scanf("%d",&n);
	bit* b = new bit(n);bit_max* s = new bit_max(n);
	for(int i = 1;i <= n;++i){scanf("%d",&a[i]);a[i]++;}
	for(int i = n;i;--i){
		int lb = 1,ub = n;
		while(lb <= ub){
			int mid = (lb + ub) >> 1;
			if(b->sum(mid) <= mid - a[i])ub = mid - 1,pos[i] = mid;
			else lb = mid + 1;
		}
		b->add(pos[i],1);
	}
	for(int i = 1;i <= n;++i){
		f[i] = s->ask_max(pos[i]) + 1;
		s->add(pos[i],f[i]);
		f[i] = std::max(f[i],f[i - 1]);
		printf("%d\n",f[i]);
	}
	return 0;
}