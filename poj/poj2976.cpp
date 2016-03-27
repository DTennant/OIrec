#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#define MAX_N 1100
using namespace std;
int N,K;double x;
struct Test{
	int a,b;
	bool operator < (const Test& rhs) const {
		return a - x * b > rhs.a - x * rhs.b;
	}
}test[MAX_N];
bool C(double mid){
	x = mid;
	sort(test + 1,test + 1 + N);
	double total_a = 0.0,total_b = 0.0;
	for(int i = 1;i <= N - K;++i){
		total_a += test[i].a;
		total_b += test[i].b;
	}
	return total_a / total_b > mid;
}
int main(){
	while(cin >> N >> K && (N || K)){
		for(int i = 1;i <= N;++i)cin >> test[i].a;
		for(int i = 1;i <= N;++i)cin >> test[i].b;
		double lb = 0.0,ub = 1.0;
		while(abs(ub - lb) > 1e-4){
			double mid = (ub + lb) / 2;
			(C(mid) ? lb : ub) = mid;
		}
		cout << fixed << setprecision(0) << lb * 100 << endl;
	}
	return 0;
}