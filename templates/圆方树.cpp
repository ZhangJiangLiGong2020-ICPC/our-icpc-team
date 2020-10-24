#include<cstdio>
#define neko 200010
#define meko 200010
#define chkmin(a,b) ((a)<(b)?(a):(b))
#define f(i,a,b) for(register int i=(a);i<=(b);i=-(~(i)))
#define travel(i,u,v) for(register int i=head[u],v=e[i].v;i;i=e[i].nex,v=e[i].v)
typedef int arr[neko];
arr dfn,s,low,head,Head;
int n,m;long long ans,nown;
typedef long long arl[neko];
arl siz,tim,val;
struct node
{
	int u,v,nex;
}e[meko<<1],E[meko<<1];
namespace CS_Tree
{
	int t=0,now,cnt,tp=0,dfc=0,las;
	void add(int x,int y)
	{
		E[++t].v=y;
		E[t].u=x;
		E[t].nex=Head[x];
		Head[x]=t;
		E[++t].v=x;
		E[t].u=y;
		E[t].nex=Head[y];
		Head[y]=t;
		val[x]=-1;
	}
	void dfs(int u)
	{
		dfn[u]=low[u]=++dfc;++nown;
		s[++tp]=u;
		for(register int i=head[u],v=e[i].v;i;i=e[i].nex,v=e[i].v)
		{
			if(!dfn[v])
			{
				dfs(v);
				low[u]=chkmin(low[u],low[v]);
				if(dfn[u]<=low[v])
				{
					++cnt,now=0;
					do{add(las=s[tp--],cnt),++now;}while(las^v);
					add(u,cnt),val[cnt]=++now;
				}
			}
			else low[u]=chkmin(low[u],dfn[v]);
		}
	}
	void debug()
	{f(i,1,t)printf("%d %d %lld %lld\n",E[i].u,E[i].v,val[E[i].u],val[E[i].v]);}
}
namespace solve
{
	int t=0;
	void dfs(int u,int fa)
	{
		if(u<=n)siz[u]=1;
		for(register int i=Head[u],v=E[i].v;i;i=E[i].nex,v=E[i].v)
		{
			if(v^fa)
			{
				dfs(v,u);
				tim[u]+=siz[u]*siz[v]*val[u]*2;
				siz[u]+=siz[v];
			}
		}
		tim[u]+=siz[u]*(nown-siz[u])*val[u]*2;
		ans+=tim[u];
	}
	void add(int x,int y)
	{
		e[++t].v=y;
		e[t].nex=head[x];
		head[x]=t;
	}
}
int main()
{
	int x,y;
	scanf("%d%d",&n,&m);
	f(i,1,m)scanf("%d%d",&x,&y),solve::add(x,y),solve::add(y,x);
	CS_Tree::cnt=n;f(i,1,n)if(!dfn[i])nown=0,CS_Tree::dfs(i),solve::dfs(i,0);
	//f(i,1,n)printf("%d %d\n",dfn[i],low[i]);
	printf("%lld\n",ans);
}
