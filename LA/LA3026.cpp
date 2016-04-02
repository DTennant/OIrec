#include <cstdio>
#define MAX_N 1000100
using namespace std;
char P[MAX_N];
int f[MAX_N],n;
int main(){
	for(int kase = 1;~scanf("%d",&n) && n;++kase){
		scanf("%s",P);
		f[0] = f[1] = 0;
		for(int i = 1;i < n;++i){
			int j = f[i];
			while(j && P[i] != P[j])j = f[j];
			f[i + 1] = (P[i] == P[j] ? j + 1 : 0);
		}
		printf("Test case #%d\n",kase);
		for(int i = 2;i <= n;++i){
			if(f[i] > 0 && (i % (i - f[i]) == 0))printf("%d %d\n",i,i / (i - f[i]));
		}
		putchar('\n');
	}
	return 0;
}