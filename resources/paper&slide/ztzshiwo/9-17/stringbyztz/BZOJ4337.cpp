#include<queue>
#include<vector>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define mem(a,b) memset(a,b,sizeof(a))
#define  For(i,a,b) for(int i=a,i##E=b;i<=i##E;++i)
#define rFor(i,a,b) for(int i=a,i##E=b;i>=i##E;--i)
using namespace std;
typedef unsigned long long LL;
const int N=60;
const LL A=233333;
const LL P=1000007;
const LL B=19260817;
template<typename T>inline bool chkmin(T &a,const T &b){return a>b?a=b,1:0;}
template<typename T>inline bool chkmax(T &a,const T &b){return a<b?a=b,1:0;}
template<typename T>inline void read(T &x)
{
    x=0;int _f(0);char ch=getchar();
    while(!isdigit(ch))_f|=(ch=='-'),ch=getchar();
    while( isdigit(ch))x=x*10+ch-'0',ch=getchar();
    x=_f?-x:x;
}
inline void file()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
}
int m,ans[N];
struct Tree
{
    int n,sz[N],p[N],q[N],cnt;
    int ls,rs,pre[N],len,c[N],dis[N];
    int bgn[N],nxt[N<<1],to[N<<1],E;
    vector<LL>G;
    LL Hash,val[N];
    Tree(){n=E=0;mem(bgn,0);}
    inline void add_edge(int u,int v){nxt[++E]=bgn[u],bgn[u]=E,to[E]=v;}
    inline int bfs(int S)
    {
        int Max=0,node=S;
        queue<int>q;
        mem(dis,0);
        dis[S]=1;
        q.push(S);
        while(!q.empty())
        {
            int u=q.front();q.pop();
            if(Max<dis[u])
            {
                node=u;
                Max=dis[u];
            }
            for(int v,i=bgn[u];i;i=nxt[i])
                if(!dis[v=to[i]])
                    dis[v]=dis[u]+1,pre[v]=u,q.push(v);
        }
        return node;
    }
    inline void Get_root()
    {
        ls=bfs(1);mem(pre,0);rs=bfs(ls);
        int x=rs;
        while(x!=0)c[++len]=x,x=pre[x];
        if(len&1)
            q[++cnt]=c[len/2+1],p[c[len/2+1]]=1;
        else
            q[++cnt]=c[len/2+1],p[c[len/2+1]]=1,
            q[++cnt]=c[len/2],p[c[len/2]]=1;
    }
    inline void dfs_Hash(int u,int f)
    {
        for(int v,i=bgn[u];i;i=nxt[i])
        if(!p[v=to[i]])
        {
            if(v==f)continue;
            dfs_Hash(v,u);
        }
        for(int v,i=bgn[u];i;i=nxt[i])
        if(!p[v=to[i]])
        {
            if(v==f)continue;
            G.push_back(val[v]);
        }
        sort(G.begin(),G.end());
        val[u]=A;
        For(i,0,G.size()-1)val[u]=(val[u]*P)^G[i];
        val[u]*=B;
        G.clear();
    }
    inline void Build_tree()
    {
        int x;
        read(n);
        For(i,1,n)
        {
            read(x);
            if(x)add_edge(x,i),add_edge(i,x);
        }
        Get_root();
        For(i,1,cnt)dfs_Hash(q[i],0);
        if(cnt>1&&val[q[1]]>val[q[2]])swap(q[1],q[2]);
        Hash=cnt>1?(((A*P^val[q[1]])*P^val[q[2]])*B):val[q[1]];
    }
}t[N];
int main()
{
    file();
    read(m);
    For(i,1,m)t[i].Build_tree();
    For(i,1,m)
        For(j,1,i)
            if(t[i].n==t[j].n&&t[i].Hash==t[j].Hash&&t[i].len==t[j].len)
            {
                ans[i]=j;
                break;
            }
    For(i,1,m)printf("%d\n",ans[i]);
    return 0;
}
