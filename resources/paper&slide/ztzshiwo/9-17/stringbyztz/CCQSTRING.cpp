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
typedef long long LL;
const int N=1000010;
const int M=25000010;
template<typename T>inline bool chkmin(T &a,const T &b){return a>b?a=b,1:0;}
template<typename T>inline bool chkmax(T &a,const T &b){return a<b?a=b,1:0;}
template<typename T>inline void read(T &x)
{
	x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while( isdigit(ch))x=x*10+(ch-'0'),ch=getchar();
}
inline void file()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
}
int n,Q,B2[N];
LL pres[N];
char s[N],str[20];
int rt[N],lc[M],rc[M],sum[M],tot;
inline void init(){For(i,1,n)B2[i]=(i>=(1<<(B2[i-1]+1)))?B2[i-1]+1:B2[i-1];}
struct node
{
	int id,x[2];
	node(){}
	node(int id,int a,int b):id(id){x[0]=a,x[1]=b;}
}rn[N],rp[N];
int sa[N],rnk[N],hei[N],c[N],m;
int rmq[N][21];
inline void Get_height()
{
	int h=0;
	For(i,1,n)
	{
		int k=sa[rnk[i]-1];
		if(h)h--;
		while(s[i+h]==s[k+h])h++;
		hei[rnk[i]]=h;
	}
	For(i,1,n)rmq[i][0]=hei[i+1];
	For(j,1,20)
		For(i,1,n-(1<<(j-1))+1)
			rmq[i][j]=min(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
}
inline int Query(int x,int y)
{
	if(x==y)return n-sa[x]+1;
	if(x>y)swap(x,y);y--;
	int ret=B2[y-x+1];
	return min(rmq[x][ret],rmq[y-(1<<ret)+1][ret]);
}
inline void Radix_Sort(node *A,node *B)
{
	rFor(k,1,0)
	{
		memset(c,0,(m+1)*sizeof(int));
		For(i,1,n)c[A[i].x[k]]++;
		For(i,1,m)c[i]+=c[i-1];
		rFor(i,n,1)B[c[A[i].x[k]]--]=A[i];
		swap(A,B);
	}
	For(i,1,n)
	{
		rnk[A[i].id]=rnk[A[i-1].id];
		if(A[i].x[0]!=A[i-1].x[0]||A[i].x[1]!=A[i-1].x[1])rnk[A[i].id]++;
	}m=rnk[A[n].id];
}
inline void Build_sa()
{
	m=30;
	For(i,1,n)rn[i]=node(i,s[i]-'a'+1,0);
	Radix_Sort(rn,rp);
	for(int k=1;k<=n&&m!=n;k<<=1)
	{
		For(i,1,n)rn[i]=node(i,rnk[i],i+k>n?0:rnk[i+k]);
		Radix_Sort(rn,rp);
	}
	For(i,1,n)sa[rnk[i]]=i;
	Get_height();
}
inline void insert(int now,int pre,int x)
{
	int l=1,r=n;
	sum[now]=sum[pre]+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(x<=mid)
			lc[now]=++tot,rc[now]=rc[pre],
			pre=lc[pre],r=mid;
		else
			lc[now]=lc[pre],rc[now]=++tot,
			pre=rc[pre],l=mid+1;
		sum[now=tot]=sum[pre]+1;
	}
}
inline int Query_kth(int l,int r,int x,int y,int k)
{
	if(l==r)return l;
	int mid=(l+r)>>1,h=sum[lc[x]]-sum[lc[y]];
	if(k<=h)
		return Query_kth(l,mid,lc[x],lc[y],k);
	else
		return Query_kth(mid+1,r,rc[x],rc[y],k-h);
}
inline int Query_rank(int l,int r,int x,int y,int k)
{
	if(l==r)return sum[x]-sum[y];
	int mid=(l+r)>>1,h=sum[lc[x]]-sum[lc[y]];
	if(k<=mid)
		return Query_rank(l,mid,lc[x],lc[y],k);
	else
		return Query_rank(mid+1,r,rc[x],rc[y],k)+h;
}
inline void Select(LL r1,LL r2)
{
	int l=1,r=n,pos=0,rpos=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(pres[mid]>=r1)pos=mid,r=mid-1;
		else l=mid+1;
	}
	int len=(r1-pres[pos-1])+hei[pos];
	l=pos,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(Query(pos,mid)>=len)rpos=mid,l=mid+1;
		else r=mid-1;
	}
	int bgn=Query_kth(1,n,rt[rpos],rt[pos-1],r2);
	printf("%d %d\n",bgn,bgn+len-1);
}
inline void Rank(int L,int R)
{
	int x=rnk[L],len=R-L+1;
	int l=1,r=x,lpos=0,rpos=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(Query(mid,x)>=len)lpos=mid,r=mid-1;
		else l=mid+1;
	}
	l=x,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(Query(mid,x)>=len)rpos=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%lld %d\n",pres[lpos-1]+len-hei[lpos],Query_rank(1,n,rt[rpos],rt[lpos-1],L));
}
int main()
{
	LL x,y;
	file();
	scanf("%s",s+1);
	n=strlen(s+1);
	init();
	Build_sa();
	For(i,1,n)
	{
		insert(rt[i]=++tot,rt[i-1],sa[i]);
		pres[i]=pres[i-1]+(n-sa[i]+1)-hei[i];
	}
	read(Q);
	while(Q--)
	{
		scanf("%s",str);read(x),read(y);
		if(str[0]=='S')
			Select(x,y);
		else
			Rank(x,y);
	}
	return 0;
}
