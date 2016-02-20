//UVaLive3971
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#define MAX_N 1010
using namespace std;
int cnt,T,N,B;
char type[30],name[30];
map<string,int> id;
int ID(string s){
	if(!id.count(s))id[s] = cnt++;
	return id[s];
}
struct Component{
	int price,quality;
};
vector<Component> comp[MAX_N];
bool C(int q){
	int sum = 0;
	for(int i = 0;i < cnt;++i){
		int cheapest = B + 1,m = comp[i].size();
		for(int j = 0;j < m;++j){
			if(comp[i][j].quality >= q)cheapest = min(cheapest,comp[i][j].price);
		}
		if(cheapest == B + 1)return false;
		sum += cheapest;
		if(sum > B)return false;
	}
	return true;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&N,&B);
		int maxq = 0;cnt = 0;
		for(int i = 0;i < N;++i)comp[i].clear();
		id.clear();
		for(int i = 0,p,q;i < N;++i){
			scanf("%s%s%d%d",type,name,&p,&q);
			maxq = max(maxq,q);
			comp[ID(type)].push_back((Component){p,q});
		}
		int L = 0,R = maxq;
		while(L < R){
			int M = L + (R - L + 1) / 2;
			if(C(M))L = M;else R = M - 1;
		}
		printf("%d\n",L);
	}
	return 0;
}