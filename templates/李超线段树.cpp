//该题为CF932F.部分内容详见博客.
#include<cstdio>
#include<cstring>
#include<iostream>
#define f(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;i=-(~i))
#define travel(i,u,v) for(register int i=head[u],v=e[i].v;i;i=e[i].nex,v=e[i].v)
const int neko=100010,steko=neko*17*2;
typedef long long ll;
int n,m,t,head[neko];
ll a[neko],b[neko],dp[neko];
int L[steko],R[steko],rt[steko];
struct Line
{ll k,b;int id;}Adv[steko];
struct node
{int v,nex;}e[neko<<1];
void add(int x,int y)
{
	e[++t].v=y,e[t].nex=head[x],head[x]=t;
	e[++t].v=x,e[t].nex=head[y],head[y]=t;
}
namespace LiC_Tree
{
#define lson L[root],l,mid
#define rson R[root],mid+1,r
	const int lim=200000,las=100000;
	int cnt=0;
	using std::swap;
	ll F(Line y,int x)
	{return y.k*x+y.b;}
	bool check(Line A,Line B,int x)
	{return F(A,x)<=F(B,x);}
	void cover(int &root,int l,int r,Line y)
	{
		if(!root)root=++cnt;
		int mid=l+r>>1;
		//printf("%d %lld %lld %lld %lld\n",mid,Adv[root].k,y.k,F(Adv[root],mid),F(y,mid));
		if(!Adv[root].id||check(y,Adv[root],mid))swap(Adv[root],y);
		if(!y.id||l==r||Adv[root].k==y.k)return;
		if(Adv[root].k<y.k)cover(lson,y);
		else cover(rson,y);
	}
	Line query(int root,int l,int r,int tag)
	{
		if(l==r)return Adv[root];
		int mid=l+r>>1;Line tmp;
		if(tag<=mid)tmp=query(lson,tag);
		else tmp=query(rson,tag);
		if(tmp.id)return check(tmp,Adv[root],tag)?tmp:Adv[root];
		else return Adv[root];
	}
	int merge(int x,int y,int l,int r)
	{
		if(!x||!y)return x|y;
		int mid=l+r>>1;
		L[x]=merge(L[x],L[y],l,mid);
		R[x]=merge(R[x],R[y],mid+1,r);
		//printf("merging %d\n",Adv[y].id);
		cover(x,l,r,Adv[y]);
		return x;
	}
	void dfs(int u,int fa)
	{
		travel(i,u,v)if(v^fa)dfs(v,u),rt[u]=merge(rt[u],rt[v],1,lim);
		int x=query(rt[u],1,lim,a[u]+las).id;//x=u后代而不是儿子
		dp[u]=a[u]*b[x]+dp[x];
		cover(rt[u],1,lim,(Line){b[u],dp[u]-b[u]*las,u});//k(x-las)+b
		//printf("%d %d\n",u,query(rt[u],1,lim,a[1]+las).id);
	}
}
int main()
{
	int x,y;
	scanf("%d",&n);
	f(i,1,n)scanf("%lld",&a[i]);
	f(i,1,n)scanf("%lld",&b[i]);
	f(i,2,n)scanf("%d%d",&x,&y),add(x,y);
	memset(Adv,0,sizeof Adv);
	LiC_Tree::dfs(1,0);
	f(u,1,n)printf("%lld%c",dp[u],u^uend?' ':'\n');
}
