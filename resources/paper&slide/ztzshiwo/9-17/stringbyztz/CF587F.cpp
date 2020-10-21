#include<queue>
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
const int N=200010;
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
int n,Q,s[N][26],tot=1,cnt;
int ls[N],rs[N],f[N],last[N];
int Block,dfn;
LL ans[N],sum[N],pres[N],S[N],sz[N];
int belong[N],ln[N],rn[N];
vector<int>G[N];
string str[N];
struct node
{
	int x,y,id;LL flag;
	node(){}
	node(int x,int y,int id,LL flag):x(x),y(y),id(id),flag(flag){}
}Situ2[N];
inline bool cmp(node A,node B){return A.x<B.x;}
vector<node>Situ1[N];
inline int insert(string a)
{
	int p=1;
	For(i,0,a.length()-1)
	{
		int x=a[i]-'a';
		p=s[p][x]?s[p][x]:s[p][x]=++tot;
	}
	return p;
}
inline void init(){tot=1;For(i,0,25)s[0][i]=1;}
inline void Get_fail(int u)
{
	For(i,0,25)
	{
		int x=s[f[u]][i];
		if(s[u][i])f[s[u][i]]=x;
		else s[u][i]=x;
	}
}
inline void Build_ac()
{
	queue<int>q;
	q.push(1);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		For(i,0,25)if(s[u][i])q.push(s[u][i]);
		Get_fail(u);
	}
	For(i,2,tot)G[f[i]].push_back(i);
}
inline void dfs(int u)
{
	ls[u]=++dfn;
	For(i,0,G[u].size()-1)dfs(G[u][i]);
	rs[u]=dfn;
}
inline void dfs_sum(int u)
{
	For(i,0,G[u].size()-1)
	{
		dfs_sum(G[u][i]);
		sum[u]+=sum[G[u][i]];
	}
}
inline void Solve1(int u)
{
	mem(sum,0);
	int p=1;
	For(i,0,str[u].length()-1)
	{
		int x=str[u][i]-'a';
		p=s[p][x];
		sum[p]++;
	}
	dfs_sum(1);
	For(i,1,n)pres[i]=pres[i-1]+sum[last[i]];
	For(i,0,Situ1[u].size()-1)
	{
		node now=Situ1[u][i];
		ans[now.id]+=pres[now.x]*now.flag;
	}
}
inline void Add_node(int l,int r)
{
	if(belong[l]==belong[r])
		For(i,l,r)S[i]++;
	else
	{
		For(i,l,rn[belong[l]])S[i]++;
		For(i,ln[belong[r]],r)S[i]++;
		For(i,belong[l]+1,belong[r]-1)sz[i]++;
	}
}
inline LL Get_ans(int x){return sz[belong[x]]+S[x];}
int main()
{
	int l,r,k;
	file();
	init();
	read(n),read(Q);
	Block=300;
	For(i,1,n)
	{
		cin>>str[i];
		last[i]=insert(str[i]);
	}
	Build_ac();
	dfs(1);
	For(i,1,tot)belong[i]=i/Block+1;
	ln[1]=1;
	For(i,1,tot)
		if(belong[i]!=belong[i+1])
		{
			rn[belong[i]]=i;
			ln[belong[i+1]]=i+1;
		}
	For(i,1,Q)
	{
		read(l),read(r),read(k);--l;
		if((int)str[k].length()>Block)
		{
			Situ1[k].push_back(node(r,k,i,1));
			Situ1[k].push_back(node(l,k,i,-1));
		}
		else
		{
			Situ2[++cnt]=node(r,k,i,1);
			Situ2[++cnt]=node(l,k,i,-1);
		}
	}
	For(i,1,n)if(Situ1[i].size())Solve1(i);
	int nowp=0;
	sort(Situ2+1,Situ2+cnt+1,cmp);
	For(i,1,cnt)
	{
		node now=Situ2[i];
		while(nowp<now.x)
		{
			nowp++;
			if((int)str[nowp].size()<=Block)
				Add_node(ls[last[nowp]],rs[last[nowp]]);
		}
		int p=1;
		For(i,0,str[now.y].length()-1)
		{
			int x=str[now.y][i]-'a';
			p=s[p][x];
			ans[now.id]+=now.flag*Get_ans(ls[p]);
		}
	}
	For(i,1,Q)printf("%lld\n",ans[i]);
	return 0;
}
