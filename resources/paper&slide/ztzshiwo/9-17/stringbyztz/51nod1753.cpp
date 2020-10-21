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
const int N=300010;
const LL mod=1000007;
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
int n,T,fa[27];
char str[N],s[5];
LL x[N][27],qp[N];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline void init_hash()
{
	qp[0]=1;
	For(i,1,n)
	{
		qp[i]=qp[i-1]*mod;
		For(j,1,26)
			x[i][j]=x[i-1][j]*mod;
		x[i][str[i]-'a'+1]++;
	}
}
inline void combine(int x,int y)
{
	if((x=find(x))!=(y=find(y)))
		fa[x]=y;
}
inline LL Get_hash(int l,int r)
{
	if(l>r)return 0;
	LL ret=0;
	For(i,1,26)
		ret=ret+(x[r][i]-x[l-1][i]*qp[r-l+1])*find(i);
	return ret;
}
inline bool Solve(int l1,int r1,int l2,int r2)
{
	if(r1-l1!=r2-l2)return 0;
	int l=1,r=r1-l1+1,ans=0;
	while(l<=r)
	{
		 int mid=(l+r)>>1;
		 if(Get_hash(l1,l1+mid-1)==Get_hash(l2,l2+mid-1))
			 ans=mid,l=mid+1;
		 else
			 r=mid-1;
	}
	if(Get_hash(l1+ans+1,r1)==Get_hash(l2+ans+1,r2))
		return 1;
	return 0;
}
int main()
{
	int k,l1,l2,r1,r2;
	scanf("%s",str+1);
	n=strlen(str+1);
	init_hash();
	read(T);
	while(T--)
	{
		For(i,1,26)fa[i]=i;
		read(k),read(l1),read(r1),read(l2),read(r2);
		For(i,1,k)
		{
			scanf("%s",s+1);
			combine(s[1]-'a'+1,s[2]-'a'+1);
		}
		if(Solve(l1,r1,l2,r2))
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
