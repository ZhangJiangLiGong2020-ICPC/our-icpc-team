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
const int N=500010;
const LL p=1e5+7;
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
int n,Q,P[N],pr[N],cnt;
char str[N];
LL Hash[N],qp[N];
inline void init()
{
	qp[0]=1;
	For(i,1,n)
	{
		Hash[i]=Hash[i-1]*p+str[i]-'a'+1;
		qp[i]=qp[i-1]*p;
	}
	For(i,2,n)
	{
		if(!P[i])P[i]=i,pr[++cnt]=i;
		for(int j=1;j<=cnt&&i*pr[j]<=n;++j)
		{
			P[i*pr[j]]=pr[j];
			if(i%pr[j]==0)break;
		}
	}
}
inline LL Get_Hash(int l,int r){return Hash[r]-Hash[l-1]*qp[r-l+1];}
int main()
{
	file();
	int l,r;
	read(n);
	scanf("%s",str+1);
	init();
	read(Q);
	while(Q--)
	{
		read(l),read(r);
		int len=r-l+1;
		int now=len;
		for(;now>1;)
		{
			int x=P[now];
			while(len%x==0&&Get_Hash(l+len/x,r)==Get_Hash(l,r-len/x))len/=x;
			while(now%x==0)now/=x;
		}
		printf("%d\n",len);
	}
	return 0;
}
