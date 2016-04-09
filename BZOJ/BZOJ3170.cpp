#include <iostream>
#include <algorithm>
#define MAX_N 100100
using namespace std;
typedef long long ll;
pair<ll, int> X[MAX_N],Y[MAX_N];
struct Point{
	ll a,b,x,y;
	void read(int id){
		cin >> a >> b;
		x = a - b;y = a + b;
		X[id] = make_pair(x,id);
		Y[id] = make_pair(y,id);
	}
}points[MAX_N];
ll sum_x[MAX_N],sum_y[MAX_N],ans[MAX_N];
int main(){
	static int N;
	cin >> N;
	for(int i = 1;i <= N;++i)points[i].read(i);
	sort(X + 1,X + 1 + N);sort(Y + 1,Y + 1 + N);
	for(int i = 2;i <= N;++i)X[i].first -= X[1].first,Y[i].first -= Y[1].first;
	X[1].first = Y[1].first = 0;
	for(int i = 1;i <= N;++i){
		sum_x[i] = sum_x[i - 1] + X[i].first;
		sum_y[i] = sum_y[i - 1] + Y[i].first;
	}
	for(int i = 1;i <= N;++i){
		ans[X[i].second] += X[i].first * (i - 1) - sum_x[i - 1];
		ans[X[i].second] += (sum_x[N] - sum_x[i]) - X[i].first * (N - i);
		ans[Y[i].second] += Y[i].first * (i - 1) - sum_y[i - 1];
		ans[Y[i].second] += (sum_y[N] - sum_y[i]) - Y[i].first * (N - i);
	}
	cout << *min_element(ans + 1,ans + 1 + N) / 2 << endl;
	return 0;
}