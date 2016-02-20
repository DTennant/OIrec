//UVa11520.cpp
#include <cstdio>
#include <cstring>
#define MAX_N 20
using namespace std;
char grid[MAX_N][MAX_N];
int T,N;
int main(){
	scanf("%d",&T);
	for(int kase = 1;kase <= T;++kase){
		printf("Case %d:\n",kase);
		scanf("%d",&N);
		for(int i = 0;i < N;++i){
			scanf("%s",grid[i]);
		}
		for(int i = 0;i < N;++i){
			for(int j = 0;j < N;++j){
				if(grid[i][j] == '.'){
					for(char ch = 'A';ch <= 'Z';++ch){
						bool ok = true;
						if(i > 0 && grid[i - 1][j] == ch)ok = false;
						if(i < N - 1 && grid[i + 1][j] == ch)ok = false;
						if(j > 0 && grid[i][j - 1] == ch)ok = false;
						if(j < N - 1 && grid[i][j + 1] == ch)ok = false;
						if(ok){grid[i][j] = ch;break;}
					}
				}
			}
		}
		for(int i = 0;i < N;++i){
			puts(grid[i]);
		}
	}
	return 0;
}