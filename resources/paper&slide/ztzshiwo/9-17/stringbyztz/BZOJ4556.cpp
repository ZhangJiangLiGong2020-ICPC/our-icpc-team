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
const int N=100010;
const int M=2000010;
template<typename T>inline bool chkmax(T &A,T B){return A>B?0:A=B,1;}
template<typename T>inline bool chkmin(T &A,T B){return A<B?0:A=B,1;}
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
int n,q,B2[N],a,b,c,d;
char s[N];
inline void init(){For(i,2,n)B2[i]=(1<<(B2[i-1]+1))<=i?B2[i-1]+1:B2[i-1];}
struct SuffixArray
{
	struct node
	{
		int id,x[2];
		node(){}
		node(int id,int a,int b):id(id){x[0]=a,x[1]=b;}
	}rp[N],rn[N];
	int rmq[N][18],sa[N],rnk[N],c[N],hei[N],m;
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
		for(int k=1;k<=n;k<<=1)
		{
			For(i,1,n)rn[i]=node(i,rnk[i],i+k>n?0:rnk[i+k]);
			Radix_Sort(rn,rp);
			if(m>=n)break;
		}
		For(i,1,n)sa[rnk[i]]=i;
		Get_height();
	}
	inline void Get_height()
	{
		int h=0;
		For(i,1,n)
		{
			if(!rnk[i])h=0;
			else
			{
				int k=sa[rnk[i]-1];
				if(h)h--;
				while(s[i+h]==s[k+h])h++;
			}
			hei[rnk[i]]=h;
		}
		For(i,1,n)rmq[i][0]=hei[i+1];
		For(j,1,17)
			For(i,1,n-(1<<(j-1))+1)
				rmq[i][j]=min(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
	}
	inline int Query(int x,int y)
	{
		if(x==y)return n-x+1;
		x=rnk[x],y=rnk[y];
		if(x>y)swap(x,y);y--;
		int ret=B2[y-x+1];
		return min(rmq[x][ret],rmq[y-(1<<ret)+1][ret]);
	}
}S;
int rt[N],sum[M],lc[M],rc[M],cnt;
inline void insert(int now,int pre,int x)
{
	int l=1,r=n;
	sum[now]=sum[pre]+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(x<=mid)
			lc[now]=++cnt,rc[now]=rc[pre],pre=lc[pre],r=mid;
		else
			lc[now]=lc[pre],rc[now]=++cnt,pre=rc[pre],l=mid+1;
		sum[now=cnt]=sum[pre]+1;
	}
}
inline int Query_pre(int a,int b,int x,int l,int r)
{
	if(!(sum[a]-sum[b]))return 0;
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(x<=mid)return Query_pre(lc[a],lc[b],x,l,mid);
	else
	{
		int ret=Query_pre(rc[a],rc[b],x,mid+1,r);
		if(ret)return ret;
		return Query_pre(lc[a],lc[b],x,l,mid);
	}
}
inline int Query_suf(int a,int b,int x,int l,int r)
{
	if(!(sum[a]-sum[b]))return 0;
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(x>mid)return Query_suf(rc[a],rc[b],x,mid+1,r);
	else
	{
		int ret=Query_suf(lc[a],lc[b],x,l,mid);
		if(ret)return ret;
		return Query_suf(rc[a],rc[b],x,mid+1,r);
	}
}
inline int check(int x)
{
	int ret=0,pos;
	if(b-x+1>=a&&(pos=Query_pre(rt[b-x+1],rt[a-1],S.rnk[c],1,n)))
		chkmax(ret,S.Query(S.sa[pos],c));
	if(b-x+1>=a&&(pos=Query_suf(rt[b-x+1],rt[a-1],S.rnk[c],1,n)))
		chkmax(ret,S.Query(S.sa[pos],c));
	return ret;
}
inline int Solve()
{
	int l=1,r=d-c+1,ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)>=mid)ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
int main()
{
	file();
	read(n),read(q);init();
	scanf("%s",s+1);
	S.Build_sa();
	For(i,1,n)insert(rt[i]=++cnt,rt[i-1],S.rnk[i]);
	while(q--)
	{
		read(a),read(b),read(c),read(d);
		printf("%d\n",Solve());
	}
	return 0;
}
