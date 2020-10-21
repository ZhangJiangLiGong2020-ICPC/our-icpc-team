#include<bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define pb push_back
#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
#define mx(a,b) (a>b?a:b)
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;
using namespace std;

namespace IO
{
    const uint32 Buffsize=1<<15,Output=1<<24;
    static char Ch[Buffsize],*St=Ch,*T=Ch;
    inline char getc()
    {
        return((St==T)&&(T=(St=Ch)+fread(Ch,1,Buffsize,stdin),St==T)?0:*St++);
    }
    static char Out[Output],*nowps=Out;

    inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}
    

    template<typename T>inline void read(T&x)
    {
        x=0;static char ch;T f=1;
        for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
        for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
        x*=f;
    }

    template<typename T>inline void write(T x,char ch='\n')
    {
        if(!x)*nowps++=48;
        if(x<0)*nowps++='-',x=-x;
        static uint32 sta[111],tp;
        for(tp=0;x;x/=10)sta[++tp]=x%10;
        for(;tp;*nowps++=sta[tp--]^48);
        *nowps++=ch;
    }
}
using namespace IO;

inline void file()
{
#ifndef ONLINE_JUDGE
    freopen("ddp.in","r",stdin);
    freopen("ddp.out","w",stdout);
#endif
}

const int inf=0x3f3f3f3f,MAXN=1e6+7;

struct matrix
{
    int s[2][2];
    matrix(){s[0][0]=s[0][1]=s[1][0]=s[1][1]=-inf;}

    matrix(int x){s[0][0]=s[1][1]=0;s[0][1]=s[1][0]=-inf;}

    friend matrix operator*(matrix a,matrix b)
    {
        matrix c;
        Chkmax(c.s[0][0],b.s[0][0]+a.s[0][0]);
        Chkmax(c.s[0][0],b.s[0][1]+a.s[1][0]);
        Chkmax(c.s[0][1],b.s[0][0]+a.s[0][1]);
        Chkmax(c.s[0][1],b.s[0][1]+a.s[1][1]);
        Chkmax(c.s[1][0],b.s[1][0]+a.s[0][0]);
        Chkmax(c.s[1][0],b.s[1][1]+a.s[1][0]);
        Chkmax(c.s[1][1],b.s[1][0]+a.s[0][1]);
        Chkmax(c.s[1][1],b.s[1][1]+a.s[1][1]);
        return c;
    }

    inline int getmx()
    {return mx(mx(s[0][0],s[0][1]),mx(s[1][0],s[1][1]));}
};

static int n,m;

static int sz[MAXN],son[MAXN],g[MAXN][2],w[MAXN];

static struct edge
{
    int v,nxt;
}p[MAXN<<1];
static int head[MAXN],e;

inline void add(int u,int v){p[++e]={v,head[u]};head[u]=e;}

void dfs(int u)
{
    sz[u]=1;g[u][1]=w[u];
    for(register int v=head[u];v;v=p[v].nxt)if(!sz[p[v].v])

    {
        dfs(p[v].v);sz[u]+=sz[p[v].v];
        if(sz[p[v].v]>sz[son[u]])son[u]=p[v].v;
        g[u][0]+=mx(g[p[v].v][0],g[p[v].v][1]);
        g[u][1]+=g[p[v].v][0];
    }
}

namespace bst
{
    static matrix W[MAXN],S[MAXN];
    static int so[MAXN][2],fa[MAXN],sta[MAXN],tp;
    static int ssz[MAXN],rt;

    inline void update(int u){S[u]=S[so[u][0]]*W[u]*S[so[u][1]];}

    int build_tree(int l,int r)
    {
        if(l>r)return 0;
        static int tot;tot=0;Rep(i,l,r)tot+=ssz[sta[i]];
        for(register int i=l,cnt=ssz[sta[i]];i<=r;++i,cnt+=ssz[sta[i]])
            if(cnt*2>=tot)
            {
                int rs=build_tree(l,i-1),ls=build_tree(i+1,r);
                so[sta[i]][0]=ls,so[sta[i]][1]=rs;
                fa[ls]=fa[rs]=sta[i];update(sta[i]);
                return sta[i];
            }
    }

    inline void getpoi(int u)
    {W[u].s[0][0]=W[u].s[0][1]=**(g+u);W[u].s[1][0]=*(*(g+u)+1);}

    int build(int top,int fr)
    {
        for(int t=top;t;fr=t,t=son[t])
        {
            for(register int v=head[t];v;v=p[v].nxt)
                if(p[v].v^son[t]&&p[v].v^fr)
                    fa[build(p[v].v,t)]=t;
            getpoi(t);
        }
        tp=0;
        for(int t=top;t;t=son[t])
            sta[++tp]=t,ssz[t]=sz[t]-sz[son[t]];
        return build_tree(1,tp);
    }

    bitset<MAXN>isr;

    void modify(int u,int val)
    {
        g[u][1]+=val-w[u];
        w[u]=val;
        static int dp0[2],dp1[2];
        for(;u;u=fa[u])
        {
            dp0[0]=mx(S[u].s[0][0],S[u].s[0][1]);
            dp0[1]=mx(S[u].s[1][0],S[u].s[1][1]);
            getpoi(u);update(u);
            dp1[0]=mx(S[u].s[0][0],S[u].s[0][1]);
            dp1[1]=mx(S[u].s[1][0],S[u].s[1][1]);
            if(isr.test(u))
            {
                g[fa[u]][0]+=mx(dp1[0],dp1[1])-mx(dp0[0],dp0[1]);
                g[fa[u]][1]+=dp1[0]-dp0[0];
            }
        }
    }
}
void dfs(int u,int fr)
{
    if(!son[u])return;
    g[u][0]-=mx(g[son[u]][0],g[son[u]][1]);
    g[u][1]-=g[son[u]][0];
    for(register int v=head[u];v;v=p[v].nxt)if(p[v].v^fr)dfs(p[v].v,u);
}
using namespace bst;

inline void init()
{
    read(n);read(m);
    Rep(i,1,n)read(w[i]);
    static int u,v;
    Rep(i,1,n-1)read(u),read(v),add(u,v),add(v,u);
    dfs(1);
    dfs(1,0);
    W[0]=S[0]=matrix(0);
    rt=build(1,0);
    Rep(i,1,n)if(i^so[fa[i]][0]&&i^so[fa[i]][1])isr.set(i);
}

inline void solve()
{
    static int lasans=0;
    static int x,y;
    Rep(i,1,m)
    {
        read(x);read(y);
        x^=lasans;
        modify(x,y);
        write(lasans=S[rt].getmx());
    }
    flush();
}

int main()
{
    file();
    init();
    solve();
//    cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
    return 0;
}
