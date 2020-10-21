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
const int N=1010;
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
int T,n;
char s[N];
struct node
{
	int id,x[2];
	node(){}
	node(int id,int a,int b):id(id){x[0]=a,x[1]=b;}
}rn[N],rp[N];
int sa[N],rnk[N],hei[N],c[N],m;
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
		if(A[i].x[0]!=A[i-1].x[0]||A[i].x[1]!=A[i-1].x[1])rnk[A[i].id]++;
	}m=rnk[A[n].id];
}
inline void Build_sa()
{
	m=130;
	For(i,1,n)rn[i]=node(i,s[i]+1,0);
	Radix_Sort(rn,rp);
	for(int k=1;k<=n&&m!=n;k<<=1)
	{
		For(i,1,n)rn[i]=node(i,rnk[i],i+k>n?0:rnk[i+k]);
		Radix_Sort(rn,rp);
	}
	For(i,1,n)sa[rnk[i]]=i;
	Get_height();
}
int main()
{
	file();
	read(T);
	while(T--)
	{
		scanf("%s",s+1);
		n=strlen(s+1);
		Build_sa();
		LL ans=0;
		For(i,1,n)ans=ans+(n-sa[i]+1)-hei[i];
		printf("%lld\n",ans);
	}
	return 0;
}

