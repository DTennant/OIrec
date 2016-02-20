#include <cstdio>
#include <algorithm>
#define MAX_N 10100
using namespace std;
const char dirName[][10] = {"L","Turning","R"};
struct Ant{
	int id,pos,dir;
	bool operator < (const Ant &A) const {
		return pos < A.pos;
	}
}before[MAX_N],after[MAX_N];
int N,L,T,n,order[MAX_N],ch;
int main(){
	scanf("%d",&N);
	for(int kase = 1;kase <= N;++kase){
		printf("Case #%d:\n",kase);
		scanf("%d%d%d",&L,&T,&n);
		for(int i = 0,p,d;i < n;++i){
			scanf("%d %c",&p,&ch);
			d = (ch == 'L' ? -1 : 1);
			before[i] = (Ant){i,p,d};
			after[i] = (Ant){0,p + T * d,d};
		}
		sort(before,before + n);
		for(int i = 0;i < n;++i){
			order[before[i].id] = i;
		}
		sort(after,after + n);
		for(int i = 0;i < n - 1;++i){
			if(after[i].pos == after[i + 1].pos)
				after[i].dir = after[i + 1].dir = 0;
		}
		for(int i = 0;i < n;++i){
			int a = order[i];
			if(after[a].pos < 0 || after[a].pos > L)puts("Fell off");
			else printf("%d %s\n",after[a].pos,dirName[after[a].dir + 1]);
		}
		putchar('\n');
	}
	return 0;
}