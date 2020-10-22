#include<cstdio>
#include<iostream>
#include<cstdlib>
#define f(i,a,b) for(register int i=(a);i<=(b);++i)
typedef unsigned int ui;
const ui neko=100010,mod=51061;
typedef ui arr[neko];
arr Mul,Add,Sum,Val,Siz,Rev;
ui ADD(ui x,ui y){return (x+=y)>=mod?x-=mod:x;}
int n,m,son[neko][2],fa[neko],s[neko];
namespace LCT
{
	int tp;
	void pushr(int x)
	{std::swap(son[x][0],son[x][1]),Rev[x]^=1;}
	void pusha(int x,ui v)
	{
		Val[x]=ADD(Val[x],v);
		Sum[x]=ADD(Sum[x],v*Siz[x]%mod);
		Add[x]=ADD(Add[x],v);
	}
	void pushm(int x,ui v)
	{
		Val[x]=Val[x]*v%mod;
		Sum[x]=Sum[x]*v%mod;
		Add[x]=Add[x]*v%mod;
		Mul[x]=Mul[x]*v%mod;
		//printf("%u %u %u\n",Sum[x],Add[x],Mul[x]);
	}
	void pushup(int x)
	{
		Sum[x]=ADD(Val[x],ADD(Sum[son[x][0]],Sum[son[x][1]]));
		Siz[x]=Siz[son[x][0]]+Siz[son[x][1]]+1;
	}
	void pushdown(int x)
	{
		if(Rev[x])pushr(son[x][0]),pushr(son[x][1]),Rev[x]=0;
		if(Mul[x]^1)pushm(son[x][0],Mul[x]),pushm(son[x][1],Mul[x]),Mul[x]=1;	
		if(Add[x])pusha(son[x][0],Add[x]),pusha(son[x][1],Add[x]),Add[x]=0;
	}
	bool isroot(int x)
	{return (son[fa[x]][0]^x)&&(son[fa[x]][1]^x);}
	bool get(int x)
	{return son[fa[x]][1]==x;}
	void rotate(int x)
	{
		int y=fa[x],z=fa[y];bool side=get(x);
		if(!isroot(y))son[z][get(y)]=x;fa[x]=z;
		fa[son[y][side]=son[x][side^1]]=y;
		fa[son[x][side^1]=y]=x;
		pushup(y),pushup(x);
	}
	void splay(int x)
	{
		int y;
		s[tp=1]=x;
		for(y=x;!isroot(y);y=fa[y])s[++tp]=fa[y];
		while(tp)pushdown(s[tp--]);
		for(y=fa[x];!isroot(x);rotate(x),y=fa[x])if(!isroot(y))rotate(get(x)^get(y)?x:y);
		pushup(x);
	}
	void access(int x)
	{for(register int y=0;x;y=x,x=fa[x])splay(x),son[x][1]=y,pushup(x);}
	void makeroot(int x)
	{access(x),splay(x),pushr(x);}
	void split(int x,int y)
	{makeroot(x),access(y),splay(y);}
	void link(int x,int y)
	{makeroot(x),fa[x]=y;}//legal defaultly
	void cut(int x,int y)
	{split(x,y),fa[x]=son[y][0]=0,pushup(y);}
}
int main()
{
	using namespace LCT;
	char opt[10];
	int x,y,o;ui z;
	scanf("%d%d",&n,&m);
	f(i,1,n)Val[i]=Mul[i]=1;
	f(i,2,n)scanf("%d%d",&x,&y),link(x,y);
	f(i,1,m)
	{
		scanf("%s%d%d",opt,&x,&y);
		if(opt[0]=='+')scanf("%u",&z),split(x,y),pusha(y,z);
		if(opt[0]=='-')scanf("%u%d",&z,&o),cut(x,y),link(z,o);
		if(opt[0]=='*')scanf("%u",&z),split(x,y),pushm(y,z);
		if(opt[0]=='/')split(x,y),printf("%u\n",ADD(Sum[y],mod));
	}return 0;
}
