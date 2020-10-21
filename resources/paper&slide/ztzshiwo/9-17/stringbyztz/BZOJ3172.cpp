#include<cmath>
#include<ctime>
#include<string>
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
const int M=1000010;
template<typename T>inline T chkmax(T A,T B){return A>B?A:B;}
template<typename T>inline T chkmin(T A,T B){return A<B?A:B;}
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
int n,tot;
char str[M];
int s[M][26],f[M],pos[M];
LL w[M];
int bgn[M],nxt[M],to[M],E;
inline void init(){tot=1;For(i,0,25)s[0][i]=1;}
inline void add_edge(int u,int v){nxt[++E]=bgn[u],bgn[u]=E,to[E]=v;}
inline void insert(char *a,int x)
{
	int p=1;
	For(i,0,strlen(a)-1)
	{
		int x=a[i]-'a';
		p=s[p][x]?s[p][x]:s[p][x]=++tot;
		w[p]++;
	}
	pos[x]=p;
}
inline void Get_fail(int p)
{
	if(f[p])add_edge(f[p],p);
	For(i,0,25)
	{
		int x=s[f[p]][i];
		if(s[p][i])f[s[p][i]]=x;
		else s[p][i]=x;
	}
}
inline void Build_ac()
{
	int q[M],h=0,t=0,p;
	for(q[++t]=1;h<t;Get_fail(p))
	{
		p=q[++h];
		For(i,0,25)if(s[p][i])q[++t]=s[p][i];
	}
}
inline void dfs(int u)
{
	for(int v,i=bgn[u];i;i=nxt[i])
		{dfs(v=to[i]);w[u]+=w[v];}
}
int main()
{
	file();
	init();
	read(n);
	For(i,1,n)
	{
		scanf("%s",str);
		insert(str,i);
	}
	Build_ac();
	dfs(1);
	For(i,1,n)printf("%lld\n",w[pos[i]]);
	return 0;
}
