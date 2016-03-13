#include <cstdio>
#include <algorithm>
#define MAX_N 100100
using namespace std;
int n,k,ids[MAX_N];double s;
struct Jewel{
	int v,w,id;
	bool operator < (const Jewel& rhs) const {
		return v - s * w > rhs.v - s * rhs.w;
	}
}jewel[MAX_N];
bool C(double mid){
	s = mid;
	sort(jewel,jewel + n);
	double total_v = 0.0,total_w = 0.0;
	for(int i = 0;i < k;++i){
		total_v += jewel[i].v;
		total_w += jewel[i].w;
	}
	return total_v / total_w > mid;
}
int main(){
	scanf("%d%d",&n,&k);
	double max_s = 0;
	for(int i = 0;i < n;++i){
		scanf("%d%d",&jewel[i].v,&jewel[i].w);
		jewel[i].id = i + 1;
		max_s = max(max_s,(double)jewel[i].v / jewel[i].w);
	}
	double lb = 0.0,ub = max_s;
	for(int i = 0;i < 50;++i){
		double mid = (lb + ub) / 2;
		if(C(mid))lb = mid;
		else ub = mid;
	}
	for(int i = 0;i < k;++i){
		ids[i] = jewel[i].id;
	}
	sort(ids,ids + k);
	for(int i = 1;i < k;++i)printf("%d ",ids[i - 1]);
	printf("%d\n",ids[k - 1]);
	return 0;
}