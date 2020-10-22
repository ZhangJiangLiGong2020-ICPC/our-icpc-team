#include<cstdio>
#include<queue>
#include<cstring>
#define f(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;i=-(~i))
const int neko=210,meko=30010,inf=2147483647;
int n,m,t=1;
struct node
{int v,cap,nex;}e[meko<<1];
int dis[neko],head[neko],cur[neko];
int cmin(int x,int y){return x<y?x:y;}
void add(int x,int y,int z)
{
	e[++t].v=y,e[t].cap=z,e[t].nex=head[x],head[x]=t;
	e[++t].v=x,e[t].cap=0,e[t].nex=head[y],head[y]=t;
}
namespace Dinic
{
	int S,T,SS,TT;
	bool bfs(int S,int T)
	{
		std::queue<int>q;	
		memset(dis,0,sizeof dis);
		q.push(S),dis[S]=1;
		int u;
		while(!q.empty())
		{
			u=q.front(),q.pop();
			for(int i=head[u],v=e[i].v;i;i=e[i].nex,v=e[i].v)if(e[i].cap&&!dis[v])
			{
				dis[v]=dis[u]+1;
				if(v==T)return 1;
				q.push(v);
			}
		}return 0;
	}
	int dfs(int u,int T,int flow)
	{
		if(u==T||!flow)return flow;
		int up,rescap=0;
		for(int &i=cur[u],v=e[i].v;i;i=e[i].nex,v=e[i].v)if(dis[v]==dis[u]+1&&(up=dfs(v,T,cmin(flow,e[i].cap))))
		{
			e[i].cap-=up,e[i^1].cap+=up;
			rescap+=up;
			if(!(flow-=up))break;
		}return rescap;
	}
	int dinic(int S,int T)
	{
		int ans=0;
		while(bfs(S,T))memcpy(cur,head,sizeof cur),ans+=dfs(S,T,inf);
		return ans;
	}
}
int main()
{
	int x,y,z,o,res=0;
	using namespace Dinic;
	scanf("%d%d%d%d",&n,&m,&S,&T),SS=n+1,TT=SS+1;
	f(i,1,m)scanf("%d%d%d%d",&x,&y,&z,&o),add(x,y,o-z),add(SS,y,z),add(x,TT,z),res+=z;
	add(T,S,inf);
	if(dinic(SS,TT)^res)return printf("please go home to sleep\n"),0;
	res=e[t].cap,e[t].cap=e[t^1].cap=0,printf("%d\n",res+dinic(S,T));
	return 0;
}
