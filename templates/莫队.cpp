//该题为luogu P1494 早年集训题 小Z的袜子.具体内容详见博客.
#include<cstdio>
#include<cmath>
#include<utility>
#include<algorithm>
#define fi first
#define se second
#define f(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;i=-(~i))
const int neko=50010;
int n,m,col[neko],cnt[neko],bl[neko],blk;
typedef std::pair<long long,long long> pi;
pi ans[neko];
int gcd(int a,int b){return b?gcd(b,a%b):a;}
struct node
{
	int l,r,id;
	bool operator <(const node &x)const
	{
		if(bl[l]==bl[x.l])
		{
			if(bl[l]&1)return r<x.r;
			return r>x.r;
		}return bl[l]<bl[x.l];
	}
}q[neko];
namespace Mo
{
	pi now=pi(0,0);int l,r;
	void add(int x,int opt)
	{
		now.se+=opt*(r-l);
		if(opt==1)now.fi+=cnt[col[x]],++cnt[col[x]];
		else --cnt[col[x]],now.fi-=cnt[col[x]];
	}
}
int main()
{
	using namespace Mo;
	int x;
	scanf("%d%d",&n,&m),blk=n/sqrt(m);
	f(i,1,n)scanf("%d",&col[i]);
	f(i,1,m)scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	f(i,1,n)bl[i]=(i-1)/blk+1;
	std::sort(q+1,q+m+1);
	l=1,r=0;
	f(i,1,m)
	{
		while(r<q[i].r)add(++r,1);
		while(r>q[i].r)add(r,-1),--r;
		while(l>q[i].l)add(--l,1);
		while(l<q[i].l)add(l,-1),++l;
		//printf("%d %d %lld\n",l,r,now.se);
		if(q[i].l==q[i].r)ans[q[i].id].fi=0,ans[q[i].id].se=1;
		else x=gcd(now.fi,now.se),ans[q[i].id].fi=now.fi/x,ans[q[i].id].se=now.se/x;
	}f(i,1,m)printf("%lld/%lld\n",ans[i].fi,ans[i].se);
}
