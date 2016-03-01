#include <cstdio>
#define MOD 100003
typedef long long ll;
ll pow(ll n,ll p){
	ll ans = 1;
	while(p){
		if(p & 1)ans = ans * n % MOD;
		n = n * n % MOD;
		p >>= 1;
	}
	return ans;
}
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main(){
	ll n,m;
	m = read();n = read();
	ll ans = pow(m,n);
	ans = (ans + MOD - m * pow(m - 1,n - 1) % MOD) % MOD;
	printf("%lld\n",ans);
	return 0;
}