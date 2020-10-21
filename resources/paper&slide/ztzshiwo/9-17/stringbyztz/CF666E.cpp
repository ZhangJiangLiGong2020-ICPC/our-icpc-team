#include<vector>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ls l,mid
#define rs mid+1,r
#define mem(a,b) memset(a,b,sizeof(a))
#define  For(i,a,b) for(int i=a,i##E=b;i<=i##E;++i)
#define rFor(i,a,b) for(int i=a,i##E=b;i>=i##E;--i)
using namespace std;
typedef long long LL;
const int N=1500010;
const int M=6000010;
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
int n,m,Q,tot,lst,cnt;
int s[N][27],Link[N],len[N];
int fa[N][21],pos[N];
char s1[N],s2[N];
int lc[M],rc[M],rt[N];
int bgn[N],nxt[N],to[N],E;
inline void add_edge(int u,int v){nxt[++E]=bgn[u],bgn[u]=E,to[E]=v;}
struct node
{
	int num,pos;
	node(){}
	node(int num,int pos):num(num),pos(pos){}
}a[M],ans[N];
inline bool operator<(node A,node B){return A.num<B.num||(A.num==B.num&&A.pos>B.pos);}
struct query
{
	int l,r,id;
	query(){}
	query(int l,int r,int id):l(l),r(r),id(id){}
};
vector<query>G[N];
inline void init(){lst=tot=1;}
inline void extend(int x)
{
	int np,p,nq,q;
	len[np=++tot]=len[p=lst]+1;
	for(;p&&!s[p][x];p=Link[p])s[p][x]=np;
	if(!p)Link[np]=1;
	else
	{
		q=s[p][x];
		if(len[q]==len[p]+1)Link[np]=q;
		else
		{
			len[nq=++tot]=len[p]+1;
			memcpy(s[nq],s[q],sizeof(s[nq]));
			Link[nq]=Link[q];Link[np]=Link[q]=nq;
			for(;p&&s[p][x]==q;p=Link[p])s[p][x]=nq;
		}
	}lst=np;
}
inline node Max(node A,node B){return A<B?B:A;}
inline void insert(int l,int r,int &p,int x)
{
	if(!p)p=++cnt;
	if(l==r){a[p].num++,a[p].pos=x;return;}
	int mid=(l+r)>>1;
	if(x<=mid)insert(ls,lc[p],x);
	else	  insert(rs,rc[p],x);
	a[p]=Max(a[lc[p]],a[rc[p]]);
}
inline int merge_tree(int l,int r,int x,int y)
{
	if(!x||!y)return x^y;
	if(l==r){a[x].num+=a[y].num;chkmin(a[x].pos,a[y].pos);return x;}
	int mid=(l+r)>>1;
	lc[x]=merge_tree(ls,lc[x],lc[y]);
	rc[x]=merge_tree(rs,rc[x],rc[y]);
	a[x]=Max(a[lc[x]],a[rc[x]]);
	return x;
}
inline void dfs_fa(int u,int f)
{
	fa[u][0]=f;
	For(i,1,20)
	{
		if(!fa[u][i-1])break;
		fa[u][i]=fa[fa[u][i-1]][i-1];
	}
	for(int i=bgn[u];i;i=nxt[i])
		dfs_fa(to[i],u);
}
inline node Query_tree(int l,int r,int p,int x,int y)
{
	if(x<=l&&r<=y)return a[p];
	int mid=(l+r)>>1;node now=node(-1,0);
	if(x<=mid)now=Max(now,Query_tree(ls,lc[p],x,y));
	if(y> mid)now=Max(now,Query_tree(rs,rc[p],x,y));
	return now;
}
inline void dfs_ans(int u)
{
	for(int v,i=bgn[u];i;i=nxt[i])
	{
		dfs_ans(v=to[i]);
		rt[u]=merge_tree(1,m,rt[u],rt[v]);
	}
	if(G[u].size())
		For(i,0,G[u].size()-1)
		{
			query now=G[u][i];
			ans[now.id]=Max(ans[now.id],Query_tree(1,m,rt[u],now.l,now.r));
		}
}
int main()
{
	file();
	int l,r,x,y;
	init();
	scanf("%s",s1+1);
	n=strlen(s1+1);
	For(i,1,n)extend(s1[i]-'a'),pos[i]=lst;
	extend(26);
	read(m);
	a[0]=node(-1,0);
	For(i,1,m)
	{
		scanf("%s",s2+1);
		For(j,1,strlen(s2+1))
			extend(s2[j]-'a'),insert(1,m,rt[lst],i);
		extend(26);
	}
	For(i,1,tot)if(Link[i])add_edge(Link[i],i);
	dfs_fa(1,0);
	read(Q);
	For(i,1,Q)
	{
		read(x),read(y),read(l),read(r);
		ans[i]=node(0,x);
		int Len=r-l+1,Pos=pos[r];
		rFor(j,20,0)
			if(len[fa[Pos][j]]>=Len)
				Pos=fa[Pos][j];
		G[Pos].push_back(query(x,y,i));
	}
	dfs_ans(1);
	For(i,1,Q)printf("%d %d\n",ans[i].pos,ans[i].num);
	return 0;
}
