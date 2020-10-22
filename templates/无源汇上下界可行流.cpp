#include<cstdio>
#include<cstring>
#include<queue>
#define f(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;i=-(~i))
using namespace std;
const int neko=210,ceko=30600*2+10,inf=2e9;
int n,m,t=1;
typedef int arr[neko];
arr head,cur,dis;
struct node
{int v,nex,cap;}e[ceko];
int lowf[ceko];
int cmin(int x,int y){return x<y?x:y;}
void add(int x,int y,int z,int o)
{
	e[++t].v=y,e[t].cap=z,lowf[t]=o,e[t].nex=head[x],head[x]=t;
	e[++t].v=x,e[t].cap=0,lowf[t]=o,e[t].nex=head[y],head[y]=t;
}
namespace Flow
{
	int SS,TT;
	bool bfs(int S,int T)
	{
		int u;
		queue<int>q;
		memset(dis,0,sizeof dis);
		q.push(S),dis[S]=1;
		while(!q.empty())
		{
			u=q.front(),q.pop();
			for(register int i=head[u],v=e[i].v;i;i=e[i].nex,v=e[i].v)if(!dis[v]&&e[i].cap)
			{
				dis[v]=dis[u]+1;
				q.push(v);
				if(v==T)return 1;
			}
		}return 0;
	}
	int dfs(int u,int flow,int T)
	{
		int up,rescap=0;
		if(!flow||u==T)return flow;
		for(register int &i=cur[u],v=e[i].v;i;i=e[i].nex,v=e[i].v)if(dis[v]==dis[u]+1&&(up=dfs(v,cmin(e[i].cap,flow),T)))
		{
			e[i].cap-=up,e[i^1].cap+=up;
			rescap+=up;
			if(!(flow-=up))break;
		}return rescap;
	}
	int dinic(int S,int T)
	{
		int ans=0;
		while(bfs(S,T))memcpy(cur,head,sizeof cur),ans+=dfs(S,inf,T);
		return ans;
	}
}
int main()
{
	using namespace Flow;
	int res=0,x,y,z,o;
	scanf("%d%d",&n,&m),SS=n+1,TT=SS+1;
	f(i,1,m)scanf("%d%d%d%d",&x,&y,&z,&o),add(x,y,o-z,z),add(SS,y,z,0),add(x,TT,z,0),res+=z;
	if(res^dinic(SS,TT))printf("NO\n");
	else
	{
		printf("YES\n");
		f(i,2,t)if((i&1)&&e[i].v<=n&&e[i].v>=1&&e[i^1].v<=n&&e[i^1].v>=1)printf("%d\n",e[i].cap+lowf[i]);//反向边残量=流量
	}
	return 0;
}
