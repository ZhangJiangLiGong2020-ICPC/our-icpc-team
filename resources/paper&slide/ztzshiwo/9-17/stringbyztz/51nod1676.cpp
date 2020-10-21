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
const int N=400;
const int M=10010;
const LL A=233333;
const LL B=1000007;
const int F=40;
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
int T,n,m;
struct graph
{
	LL dp[N][N],Hash[N];
	int bgn[N],nxt[M],to[M],E;
	inline void add_edge(int u,int v){nxt[++E]=bgn[u],bgn[u]=E,to[E]=v;}
	inline void init(){E=0;mem(dp,0);mem(bgn,0);}
	inline void Build_graph()
	{
		int x,y;
		init();
		For(i,1,m)
		{
			read(x),read(y);
			add_edge(x,y),add_edge(y,x);
		}
		For(i,1,n)dp[i][0]=1;
		For(x,1,F)
			For(u,1,n)
			{
				dp[u][x]=A*dp[u][x-1]+x;
				for(int v,i=bgn[u];i;i=nxt[i])
					dp[u][x]+=dp[v=to[i]][x-1]*B;
			}
		For(i,1,n)Hash[i]=dp[i][F];
		sort(Hash+1,Hash+n+1);
	}
}G1,G2;
int main()
{
	file();
	read(T);
	while(T--)
	{
		read(n),read(m);
		G1.Build_graph();
		G2.Build_graph();
		int flag=1;
		For(i,1,n)
			if(G1.Hash[i]!=G2.Hash[i])
			{
				flag=0;
				break;
			}
		printf("%s\n",flag?"YES":"NO");
	}
	return 0;
}
