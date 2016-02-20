#include <cstdio>
#include <vector>
#include <algorithm>
#define MAX_N 1100
using namespace std;
struct Job{
	int B,J;
	bool operator < (const Job &a) const {
		return J > a.J;
	}
};
vector<Job> ivec;
int N,C,ans,s;
int main(){
	while(scanf("%d",&N),N){
		ivec.clear();
		for(int i = 0,a,b;i < N;++i){
			scanf("%d%d",&a,&b);
			ivec.push_back((Job){a,b});
		}
		sort(ivec.begin(),ivec.end());
		ans = s = 0;
		for(int i = 0;i < N;++i){
			s += ivec[i].B;
			ans = max(ans,s + ivec[i].J);
		}
		printf("Case %d: %d\n",++C,ans);
	}
	return 0;
}