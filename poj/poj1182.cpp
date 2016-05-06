#include <cstdio>
#define MAX_N 50010 * 3
#define MAX_K 100100
using namespace std;
int f[MAX_N],t[MAX_K],a[MAX_K],b[MAX_K],n,k,ans;
void init(int n){for(int i = 0;i < n;++i)f[i] = i;}
int find(int x){return f[x] == x ? f[x] : f[x] = find(f[x]);}
bool same(int x,int y){return find(x) == find(y);}
void merge(int x,int y){x = find(x);y = find(y);if(x == y)return;f[x] = y;}
int main(){
	while(~scanf("%d%d",&n,&k)){
		for(int i = 0;i < k;++i){
			scanf("%d%d%d",&t[i],&a[i],&b[i]);
		}
		init(3 * n);ans = 0;
		for(int i = 0;i < k;++i){
			int op = t[i],x = a[i] - 1,y = b[i] - 1;
			if(x < 0 || y < 0 || x >= n || y >= n){
				ans++;continue;
			}
			if(op == 1){
				if(same(x,y + n) || same(x,y + 2 * n))ans++;
				else{
					merge(x,y);
					merge(x + n,y + n);
					merge(x + 2 * n,y + 2 * n);
				}
			}else{
				if(same(x,y) || same(x,y + 2 * n))ans++;
				else{
					merge(x,y + n);
					merge(x + n,y + 2 * n);
					merge(x + 2 * n,y);
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}