#include<vector>
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
const int N=400010;
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
int T,n,m,L,cnt,s[N];
int sa[N],rnk[N],hei[N],c[N];
int fa[N],flag;
LL ans[N],sz[N][2];
char s1[N],s2[N];
vector<int>G[N];
struct node
{
	int id,x[2];
	node(){}
	node(int id,int a,int b):id(id){x[0]=a,x[1]=b;}
}rn[N],rp[N];
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
		if(A[i].x[0]!=A[i-1].x[0]||A[i].x[1]!=A[i-1].x[1])
			rnk[A[i].id]++;
	}
	m=rnk[A[n].id];
}
inline void Build_sa()
{
	n=0,m=30;
	For(i,1,strlen(s1+1))s[++n]=s1[i]-'a'+1;
	s[++n]=30;
	For(i,1,strlen(s2+1))s[++n]=s2[i]-'a'+1;
	For(i,1,n)rn[i]=node(i,s[i],0);
	Radix_Sort(rn,rp);
	for(int k=1;k<=n&&m<n;k<<=1)
	{
		For(i,1,n)rn[i]=node(i,rnk[i],i+k>n?0:rnk[i+k]);
		Radix_Sort(rn,rp);
	}
	For(i,1,n)sa[rnk[i]]=i;
	Get_height();
}
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline LL Combine(int x,int y)
{
	LL ret=0;
	if((x=find(x))!=(y=find(y)))
	{
		ret=sz[x][0]*sz[y][1]+sz[x][1]*sz[y][0];
		sz[y][0]+=sz[x][0],sz[y][1]+=sz[x][1];
		fa[x]=y;
	}
	return ret;
}
int main()
{
	file();
	read(T);
	while(T--)
	{
		scanf("%s%s",s1+1,s2+1);
		read(L);
		Build_sa();
		For(i,2,n)G[hei[i]].push_back(i);
		flag=strlen(s1+1);
		For(i,1,n)
		{
			fa[i]=i;
			if(i==n)continue;
			sz[i][sa[i]<=flag]++;
		}
		rFor(i,n,1)
		if(G[i].size())
		{
			For(j,0,G[i].size()-1)
			{
				int pos=G[i][j];
				ans[i]+=Combine(pos-1,pos);
			}G[i].clear();
		}
		rFor(i,n,1)ans[i]+=ans[i+1];
		For(i,1,L)printf("%lld ",ans[i]);puts("");
		For(i,1,n)sz[i][0]=sz[i][1]=ans[i]=0;
	}
	return 0;
}
