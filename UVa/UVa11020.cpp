#include <cstdio>
#include <set>
using namespace std;
struct Point{
	int a,b;
	bool operator < (const Point& rhs) const {
		return a < rhs.a || (a == rhs.a && b < rhs.b);
	}
};
multiset<Point> S;
multiset<Point>::iterator it;
int main(){
	int T,n,a,b;
	scanf("%d",&T);
	for(int kase = 1;kase <= T;++kase){
		if(kase > 1)putchar('\n');
		printf("Case #%d:\n",kase);
		scanf("%d",&n);
		S.clear();
		while(n--){
			scanf("%d%d",&a,&b);
			Point P = (Point){a,b};
			it = S.lower_bound(P);
			if(it == S.begin() || (--it)->b > b){
				S.insert(P);
				it = S.upper_bound(P);
				while(it != S.end() && it->b >= b)S.erase(it++);
			}
			printf("%d\n",S.size());
		}
	}
	return 0;
}