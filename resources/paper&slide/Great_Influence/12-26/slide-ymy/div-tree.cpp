#include<bits/stdc++.h>
#include<cctype>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
using namespace std;
template<typename T>inline void read(T &x){
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&k^'-')k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
void file(void){
    #ifndef ONLINE_JUDGE
    freopen("div-tree.in","r",stdin);
    freopen("div-tree.out","w",stdout);
    #endif
}
const int MAXN=1e4+7;
static int n,m;
const int K=1e7;
static struct edge
{
    int v,w,nxt;
}p[MAXN<<1];
static int head[MAXN],e;
inline void add(int u,int v,int w,bool laz=1)
{
    p[++e].v=v;p[e].w=w;p[e].nxt=head[u];head[u]=e;
    if(laz)add(v,u,w,0);
}
void init()
{
    read(n);read(m);
    static int u,v,w;
    Rep(i,1,n-1)read(u),read(v),read(w),add(u,v,w);
}
static int root,F[MAXN],sum,vis[MAXN],sz[MAXN];
static int G[K+7];
void getroot(int u,int fa)
{
    sz[u]=1;F[u]=0;
    for(register int v=head[u];v;v=p[v].nxt)
        if(!vis[p[v].v]&&p[v].v!=fa)
        {
            getroot(p[v].v,u);
            sz[u]+=sz[p[v].v];
            Chkmax(F[u],sz[p[v].v]);
        }
    Chkmax(F[u],sum-sz[u]);
    if(F[u]<F[root])root=u;
}
static int deps[MAXN];
void getdep(int u,int fa,int dep)
{
    deps[++deps[0]]=dep;
    for(register int v=head[u];v;v=p[v].nxt)
        if(!vis[p[v].v]&&p[v].v!=fa)
            getdep(p[v].v,u,dep+p[v].w);
}
inline void calc(int u,int in,int dep)
{
    deps[0]=0;
    getdep(u,0,0);
    //cout<<deps[0]<<endl;
    //Rep(i,1,n)cout<<deps[0]
    Rep(i,1,deps[0])Rep(j,1,deps[0])
        if(in&&deps[i]+deps[j]<=K)++G[deps[i]+deps[j]];
        else if(deps[i]+deps[j]+dep<=K)--G[deps[i]+deps[j]+dep];
}
void work(int u)
{
    vis[u]=1;
    calc(u,1,0);
    for(register int v=head[u];v;v=p[v].nxt)
        if(!vis[p[v].v])
        {
            calc(p[v].v,0,p[v].w*2);
            root=0;sum=sz[p[v].v];
            getroot(p[v].v,0);
            work(p[v].v);
        }
}
void solve()
{
    sum=F[0]=n;
    getroot(1,0);
    work(root);
    static int x;
    Rep(i,1,m)
    {
        read(x);
        printf("%s\n",G[x]?"AYE":"NAY");
    }
}
int main(void){
    file();
    init();
    solve();
    return 0;
}
