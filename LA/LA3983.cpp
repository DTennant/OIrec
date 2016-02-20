#include <cstdio>
#include <algorithm>
#define MAX_N 100100
using namespace std;
int x[MAX_N],y[MAX_N],total_dist[MAX_N],total_weight[MAX_N],dist2origin[MAX_N];
int q[MAX_N],dp[MAX_N],T,c,n,w,front,rear;
int func(int i){return dp[i] - total_dist[i + 1] + dist2origin[i + 1];}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&c,&n);
		total_dist[0] = total_weight[0] = x[0] = y[0] = 0;
		for(int i = 1;i <= n;++i){
			scanf("%d%d%d",&x[i],&y[i],&w);
			total_weight[i] = total_weight[i - 1] + w;
			dist2origin[i] = abs(x[i]) + abs(y[i]);
			total_dist[i] = total_dist[i - 1] + abs(x[i] - x[i - 1]) + abs(y[i] - y[i - 1]);
		}
		front = rear = 1;
		for(int i = 1;i <= n;++i){
			while(front <= rear && total_weight[i] - total_weight[q[front]] > c)front++;
			dp[i] = func(q[front]) + total_dist[i] + dist2origin[i];
			while(front <= rear && func(i) <= func(q[rear]))rear--;
			q[++rear] = i;
		}
		printf("%d\n",dp[n]);
		if(T)putchar('\n');
	}
	return 0;
}