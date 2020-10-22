//该题为2018-08-07 NOIp Simulation T3: revive by dy0607.具体内容见pdf。
#include<cstdio>
#include<iostream>
#define neko 300010
#define cmax(a,b) ((a)>(b)?(a):(b))
#define f(i,a,b) for(register int i=(a);i<=(b);i=-(~(i))) 
#define travel(i,u,v) for(register int i=head[u],v=e[i].v;i;i=e[i].nex,v=e[i].v)
typedef unsigned long long ull;
namespace IO
{
	const unsigned int bufsize=1<<16,outsize=1<<24;
	static char ch[bufsize],*S=ch,*T=ch;
	inline char getc()
	{return ((S==T)&&(T=(S=ch)+fread(ch,1,bufsize,stdin),S==T)?0:*S++);}
	static char Out[outsize],*nowp=Out;
	inline void flush(){fwrite(Out,1,nowp-Out,stdout);nowp=Out;}
	template<typename T>
	void read(T &x)
	{
		char c=getc();x=0;
		for(;!isdigit(c);c=getc());
		for(;isdigit(c);x=(x<<1)+(x<<3)+(c^'0'),c=getc());
	}
	template<typename T>
	void write(T x,char c='\n')
	{
		if(!x)*nowp++='0';
		static unsigned int stk[50],tp=0;
		for(;x;x/=10)stk[++tp]=x%10;
		for(;tp;*nowp++=stk[tp--]^'0');*nowp++=c;
	}
}
using namespace IO;
struct node
{int v,nex;}e[neko];
int n,q,t=3,anc[neko][20],bln[neko][20],sum[neko][20],coef[neko][20];//bln:这条边在当前点分树深度下属于哪条边,anc是点;sum:这个分治重心当前子树的答案和(sub_i*val_i),方便计算答案;t=3是因为每条边编号/2正好等于存了的权值编号
typedef int arr[neko];
arr siz,msz,sub,psb,cut,ans,val,dep,head;//sub:这条边这个方向下的siz,coef代表当前点分树结构下的这条边的sub;psb:经过当前点的路径条数(passby);cut:是否处于当前点分树内;ans:这个分治重心的答案和(sigma(sum));
//这个ans*sum算贡献有点类似铁人两项，把两两子树的贡献累起来
ull nowans;
void add(int x,int y)
{
	e[++t].v=y,e[t].nex=head[x],head[x]=t;
	e[++t].v=x,e[t].nex=head[y],head[y]=t;
}
namespace NDC_Tree
{
	#define travel(i,u,v) for(register int i=head[u],v=e[i].v;i;i=e[i].nex,v=e[i].v)
	int root=0,mod=1e9+7,nown;
	template<typename T,typename L>T ADD(T a,L b){return ((a+=b)>=mod)?a-mod:a;}
	void dfsinit(int u,int fa)
	{
		siz[u]=1;
		travel(i,u,v)
		{
			if(v^fa)
			{
				dfsinit(v,u);
				siz[u]+=siz[v];
				psb[v]=1ll*(sub[i]=siz[v])*(sub[i^1]=(n-siz[v]))%mod;
				nowans=ADD(nowans,1ll*psb[v]*val[v]%mod*val[v]%mod);//val[v]指的是v代表的这条边的权值
			}
		}
	}
	void dfsroot(int u,int fa)
	{
		siz[u]=1,msz[u]=0;
		travel(i,u,v)if(!cut[v]&&v^fa)dfsroot(v,u),siz[u]+=siz[v],msz[u]=cmax(msz[u],siz[v]);
		msz[u]=cmax(msz[u],nown-siz[u]);
		if(msz[u]<msz[root])root=u;
	}
	void dfscalc(int u,int edge,int depth,int from)
	{
		register int w=edge>>1;
		anc[w][dep[w]=depth]=root,bln[w][depth]=from;
		sum[from][depth]=ADD(sum[from][depth],1ll*(coef[w][depth]=sub[edge])*val[w]%mod);//当前重心边管辖的子树各边的答案和累到sum上
		if(cut[u])return;
		travel(i,u,v)if(i^(edge^1))dfscalc(v,i,depth,from);//同v^fa
	}
	void dfs(int u,int depth)//depth:点分树上深度;
	{
		cut[u]=1;
		travel(i,u,v)
		{
			register int from=i>>1;
			dfscalc(v,i,depth,from);
			nowans=ADD(nowans,2ll*sum[from][depth]*ans[u]%mod);//把过重心的所有链答案算起来
			ans[u]=ADD(ans[u],sum[from][depth]);//累上这个点的答案
		}
		travel(i,u,v)if(!cut[v])root=0,nown=siz[v],dfsroot(v,u),dfs(root,depth+1);
	}
	void update(int edge,int addx)//edge代表(fa[edge],edge)这条边，注意不要混淆成点
	{
		register int u,from,delta=0;//from:edge这条边在当前分治结构下属于的边
		f(i,0,dep[edge])//遍历点分树
		{
			u=anc[edge][i],from=bln[edge][i];
			if(!i||(coef[edge][i]^coef[edge][i-1]))delta=1ll*coef[edge][i]*addx%mod;//算delta,相同没必要重复算
			nowans=ADD(nowans,2ll*(ans[u]-sum[from][i]+mod)*delta%mod);//除了这个子树外的答案重新算
			sum[from][i]=ADD(sum[from][i],delta),ans[u]=ADD(ans[u],delta);//更新答案
		}nowans=ADD(nowans,(2ll*val[edge]+addx)*addx%mod*psb[edge]%mod),val[edge]=ADD(val[edge],addx);
		//(w+addx)^2=w^2+addx^2+2*w*addx,w^2已经计算过
	}
	void solve()
	{
		int x,y;
		dfsinit(1,0),msz[root]=nown=n;
		dfsroot(1,0),dfs(root,0);
		write(nowans);
		while(q--)
		{
			read(x),read(y);
			update(x,y),write(nowans);
			if(q%100000==0)flush();
		}flush();
	}
}
int main()
{
	int uzless,x;
	read(uzless);
	read(n),read(q);
	f(i,2,n)read(x),read(val[i]),add(i,x);
	NDC_Tree::solve();
}//代码中有部分其实不会爆ull的未取模(2ll*...)乘法

