#include <cstdio>
#include <cstring>
using namespace std;
const int MAX_N = 2010, MAX_M = 2010;
int K, S[MAX_N][MAX_N], C[MAX_N][MAX_N];
int main(){
	int case_num;
	scanf("%d%d", &case_num, &K);
	memset(S, 0, sizeof(S));
	memset(C, 0, sizeof(C));
	C[0][0] = 1;
	for(int i = 1;i < MAX_N;++i){
		C[i][0] = C[i][i] = 1;
		for(int j = 1;j <= i;++j){
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % K;
		}
	}
	for(int i = 0;i < MAX_N - 1;++i){
		for(int j = 0;j < MAX_M - 1;++j){
			S[i + 1][j + 1] = (j <= i && C[i][j] == 0) + S[i + 1][j] + S[i][j + 1] - S[i][j];
		}
	}
	while(case_num--){
		int n, m;
		scanf("%d%d", &n, &m);
		printf("%d\n", S[n + 1][m + 1]);
	}
	return 0;
}