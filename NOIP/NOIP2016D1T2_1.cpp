#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX_N = 300010;
const int MAX_M = 600010; 
int n,m,ecnt,first[MAX_N],next[MAX_M],to[MAX_M],f[MAX_N][20],deep[MAX_N],ans[MAX_N],val[MAX_N],sta[MAX_N],MAX_D,w[MAX_N],num[1000011];
int head[MAX_N],tt[MAX_M],nn[MAX_M],father[MAX_N],vis[MAX_N];
vector<int> vec[MAX_N],vec2[MAX_N],vec3[MAX_N];
struct node{ int s,t,lca,len;}a[MAX_N];
inline int getint(){
    int w=0,q=0; char c=getchar(); while((c<'0'||c>'9') && c!='-') c=getchar();
    if(c=='-') q=1,c=getchar(); while (c>='0'&&c<='9') w=w*10+c-'0',c=getchar(); return q?-w:w;
}
inline void link(int x,int y){ next[++ecnt]=first[x]; first[x]=ecnt; to[ecnt]=y; }
inline void link2(int x,int y){ nn[++ecnt]=head[x]; head[x]=ecnt; tt[ecnt]=y; }
inline int find(int x){ if(father[x]!=x) father[x]=find(father[x]); return father[x]; }
inline void init(int x,int fa){ 
    father[x]=x; vis[x]=1;
    for(int i=head[x];i;i=nn[i]) {
        int v=tt[i];
        if(x==a[v].s&&vis[a[v].t]) a[v].lca=find(a[v].t);
        if(x==a[v].t&&vis[a[v].s]) a[v].lca=find(a[v].s);
    }
    for(int i=first[x];i;i=next[i]) {
        int v=to[i]; if(v==fa) continue; 
        deep[v]=deep[x]+1; init(v,x); father[v]=x;
        f[v][0]=x; 
    }    
}

inline int lca(int x,int y){
    if(deep[x]<deep[y]) swap(x,y); int t=0; while((1<<t)<=deep[x]) t++; t--;
    for(int i=t;i>=0;i--) if(deep[x]-(1<<i)>=deep[y]) x=f[x][i]; if(x==y) return y;
    for(int i=t;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i]; return f[x][0];
}

inline void dfs(int x,int fa){
    int now=w[x]+deep[x],cun; if(now<=MAX_D) cun=sta[now];
    for(int i=first[x];i;i=next[i]) {
        int v=to[i]; if(v==fa) continue;
        dfs(v,x);
    }//处理子树
    sta[deep[x]]+=val[x]; if(now<=MAX_D) ans[x]=sta[now]-cun;
    for(int i=0,ss=vec[x].size();i<ss;i++) sta[deep[vec[x][i]]]--;
}

inline void dfs2(int x,int fa){
    int now=deep[x]-w[x],cun; now+=300000; cun=num[now];
    for(int i=first[x];i;i=next[i]) {
        int v=to[i]; if(v==fa) continue;
        dfs2(v,x);
    }
    for(int i=0,ss=vec2[x].size();i<ss;i++) num[300000+vec2[x][i]]++;
    ans[x]+=num[now]-cun;
    for(int i=0,ss=vec3[x].size();i<ss;i++) num[300000+vec3[x][i]]--;
}

int main(){
    n=getint(); m=getint(); int x,y; for(int i=1;i<n;i++) { x=getint(); y=getint(); link(x,y); link(y,x); }
    for(int i=1;i<=n;i++) w[i]=getint(); ecnt=0;
    for(int i=1;i<=m;i++) { a[i].s=getint(),a[i].t=getint(),val[a[i].s]++; link2(a[i].s,i); link2(a[i].t,i);}
    deep[1]=1; init(1,0); for(int i=1;i<=n;i++) MAX_D=max(MAX_D,deep[i]);
    for(int j=1;j<=19;j++) for(int i=1;i<=n;i++) f[i][j]=f[f[i][j-1]][j-1]; 
    for(int i=1;i<=m;i++) {
        a[i].len=deep[a[i].s]+deep[a[i].t]-deep[a[i].lca]*2;
        vec[a[i].lca].push_back(a[i].s);
    }
    dfs(1,0); 
    for(int i=1;i<=m;i++) {
        vec2[a[i].t].push_back(deep[a[i].t]-a[i].len);
        vec3[a[i].lca].push_back(deep[a[i].t]-a[i].len);
    }
    dfs2(1,0);
    for(int i=1;i<=m;i++) if(deep[a[i].s]-deep[a[i].lca]==w[a[i].lca]) ans[a[i].lca]--;
    for(int i=1;i<=n;i++) printf("%d ",ans[i]); 
    return 0;
}
//202.99.192.68