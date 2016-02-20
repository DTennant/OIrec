#include <cstdio>
#include <algorithm>
#define MAX_N 16100
#define MAX_K 150
using namespace std;
int dp[MAX_K][MAX_N],l[MAX_K],p[MAX_K],s[MAX_K],N,K;
int leftbound[MAX_K],rightbound[MAX_K],q[MAX_K],front,rear;
struct worker{
	int l,p,s;
	bool operator < (const worker &a) const {
		return s < a.s;
	}
}a[MAX_K];
int func(int i,int k){return dp[i - 1][k] - a[i].p * k;}
int main(){
	scanf("%d%d",&N,&K);
	for(int i = 1;i <= K;++i)scanf("%d%d%d",&a[i].l,&a[i].p,&a[i].s);
	sort(a + 1,a + 1 + K);
	for(int i = 1;i <= K;++i){
		leftbound[i] = max(0,a[i].s - a[i].l);
		rightbound[i] = min(N,a[i].s + a[i].l - 1);
	}
	for(int i = 1;i <= K;++i){
		for(int j = 0;j <= rightbound[i];++j)dp[i][j] = dp[i - 1][j];
		front = 1,rear = 0;
		for(int j = leftbound[i];j < a[i].s;++j){
			while(front <= rear && func(i,j) >= func(i,q[rear]))rear--;
			q[++rear] = j;
		}
		for(int j = a[i].s;j <= rightbound[i];++j){
			while(front < rear && j - q[front] > a[i].l)front++;
			dp[i][j] = max(func(i,q[front]) + a[i].p * j,max(dp[i - 1][j],dp[i][j - 1]));
		}
		for(int j = rightbound[i] + 1;j <= N;++j)dp[i][j] = max(dp[i - 1][j],dp[i][j - 1]);
	}
	int ans = 0;
	for(int i = 1;i <= N;++i){
		ans = max(ans,dp[K][i]);
	}
	printf("%d\n",ans);
	return 0;
}

/*
#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <algorithm> 
using namespace std; 
#define lowbit(a) ((a)&(-a)) 
#define max(a, b) ((a)>(b)?(a):(b)) 
#define min(a, b) ((a)<(b)?(a):(b)) 
#define MAXN 16010 
#define MAXM 110 
#define INF 0x777777f 
typedef long long LL; 
struct node{int l, p, s;} a[MAXM]; 
int n, m, le[MAXM], re[MAXM], q[MAXM], dp[MAXM][MAXN]; 
bool cmp(const node &a, const node &b){return a.s<b.s;} 
void read(){ 
	scanf("%d%d", &n, &m); 
	for(int i = 1; i<=m; i++) 
		scanf("%d%d%d", &a[i].l, &a[i].p, &a[i].s); 
	sort(a+1, a+m+1, cmp); 
	for(int i = 1; i<=m; i++){ 
		le[i] = max(0, a[i].s-a[i].l);		//求出左边界 
		re[i] = min(n, a[i].s+a[i].l-1);	//求出右边界 
	} 
} 
void work(){ 
	int i, j, l, p, s, h, t;
	for(i = 1; i<=m; i++){ 
		for(j = 0; j<=re[i]; j++)dp[i][j] = dp[i-1][j];			//先转移第i个人不刷 
		h = 1; t = 0; 
		for(j = le[i]; j<a[i].s; j++){		//维护单调队列 
			while(h<=t&&dp[i-1][j]-j*a[i].p>=dp[i-1][q[t]]-q[t]*a[i].p) t--; 
			q[++t] = j; 
		} 
		for(j = a[i].s; j<=re[i]; j++){ 
			while(h<t&&j-q[h]>a[i].l) h++;		//若不符合就pop 
			dp[i][j] = max(dp[i][j-1], dp[i-1][j]); 
			dp[i][j] = max(dp[i][j], dp[i-1][q[h]]+(j-q[h])*a[i].p); 
		} 
		for(j = re[i]+1; j<=n; j++) 
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]); 
	} 
	int ans = 0; 
	for(int i = 1; i<=n; i++) 
		ans = max(ans, dp[m][i]); 
	printf("%d\n", ans); 
} 
int main(){ 
	read(); 
	work(); 
	return 0; 
}*/