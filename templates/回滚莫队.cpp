//该题为JOISC2014 Day1 历史研究.具体内容详见博客.
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#define f(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;i=-(~i))
using namespace std;
const int neko=100010;
int n,m,tp;
typedef int arr[neko];
arr a,b,bl,L,R,cnt,val,s;
typedef long long ll;
ll ans[neko],now,las;
struct qwq
{
	int l,r,id;
	bool operator <(const qwq &x)const
	{return bl[l]==bl[x.l]?r<x.r:l<x.l;}
}q[neko];
int blk;
ll cmax(ll x,ll y){return x>y?x:y;}
namespace Mo
{
	void build()
	{
		f(i,1,n)
		{
			bl[i]=(i-1)/blk+1;
			if(bl[i]^bl[i-1])L[bl[i]]=i,R[bl[i-1]]=i-1;
		}R[bl[n]]=n;
	}
	void add(int x)
	{++cnt[a[x]],now=cmax(now,1ll*cnt[a[x]]*val[a[x]]);}
}
int main()
{
	using namespace Mo;
	int x,l,r;
	scanf("%d%d",&n,&m),blk=n/sqrt(m);
	f(i,1,n)scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1),x=unique(b+1,b+n+1)-(b+1);
	f(i,1,x)val[i]=b[i];f(i,1,n)a[i]=lower_bound(b+1,b+x+1,a[i])-b;
	f(i,1,m)scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	build();
	sort(q+1,q+m+1);
	f(i,1,m)
	{
		if(bl[q[i].l]^bl[q[i-1].l])
		{f(j,1,x)cnt[j]=0;now=las=0,r=R[bl[q[i].l]];}
		if(bl[q[i].l]==bl[q[i].r])
		{
			f(j,q[i].l,q[i].r)add(j),s[++tp]=a[j];
			ans[q[i].id]=now;
		}
		else
		{
			l=R[bl[q[i].l]]+1;
			while(q[i].r>r)add(++r),las=now;
			while(q[i].l<l)add(--l),s[++tp]=a[l];
			ans[q[i].id]=now;
		}
		while(tp)--cnt[s[tp]],--tp;now=las;
	}f(i,1,m)printf("%lld\n",ans[i]);
	return 0;
}
