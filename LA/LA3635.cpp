//UVaLive3635.cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double PI = acos(-1.0);
const int MAX_N = 10100;
int N,F,T;
double A[MAX_N];
bool C(double mid){
	int sum = 0;
	for(int i = 0;i < N;++i)sum += floor(A[i] / mid);
	return sum >= F + 1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&N,&F);
		double maxa = -1;
		for(int i = 0,r;i < N;++i){
			scanf("%d",&r);
			A[i] = PI * r * r;maxa = max(maxa,A[i]);
		}
		double L = 0,R = maxa;
		while(R - L > 1e-5){
			double mid = (R + L) / 2;
			(C(mid) ? L : R) = mid;
		}
		printf("%.4lf\n",L);
	}
	return 0;
}