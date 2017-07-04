#include <cstdio>
#define MAX_N 100005
#define MAX_LEN 15
using namespace std;
int dir[MAX_N], n, m;
char str[MAX_N][MAX_LEN];
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)scanf("%d%s", dir + i, str[i]);
	int cur = 0;
	for(int i = 0, r, dis; i < m; ++i){
		scanf("%d%d", &r, &dis);
		r ^= dir[cur];
		if(r){
			(cur += dis) %= n;
		}else{
			(cur -= dis) %= n;
		}
		cur = (cur % n + n) % n;
	}
	printf("%s\n", str[cur]);
	return 0;
}