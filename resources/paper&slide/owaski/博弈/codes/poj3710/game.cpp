#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
#define REP(i,st,ed) for(register int i=st,i##end=ed;i<=i##end;++i)
#define DREP(i,st,ed) for(register int i=st,i##end=ed;i>=i##end;--i)
typedef long long ll;
inline int read(){
	int x;
	char c;
	int f=1;
	while((c=getchar())!='-' && (c>'9' || c<'0'));
	if(c=='-') f=-1,c=getchar();
	x=c^'0';
	while((c=getchar())>='0' && c<='9') x=(x<<1)+(x<<3)+(c^'0');
	return x*f;
}
inline ll readll(){
	ll x;
	char c;
	int f=1;
	while((c=getchar())!='-' && (c>'9' || c<'0'));
	if(c=='-') f=-1,c=getchar();
	x=c^'0';
	while((c=getchar())>='0' && c<='9') x=(x<<1ll)+(x<<3ll)+(c^'0');
	return x*f;
}
const int maxn=1e2+10,maxm=1e3+10;
int Begin[maxn],Next[maxm],to[maxm],e;
int sg[maxn],vis[maxn],stk[maxn],Top;
void add_edge(int x,int y){
	to[++e]=y;
	Next[e]=Begin[x];
	Begin[x]=e;
}
void dfs(int x,int ff){
	bool flag=0;stk[++Top]=x;vis[x]=1;
	for(int i=Begin[x];i;i=Next[i]){
		if(to[i]==ff && !flag){
			flag=1;continue;
		}
		if(vis[to[i]]==1){
			int cnt=1;
			while(stk[Top]!=to[i]){
				vis[stk[Top]]=-1;
				cnt^=1;
				--Top;
			}
			sg[to[i]]^=cnt;
		}
		else if(vis[to[i]]==0){
			dfs(to[i],x);
			if(vis[to[i]]==1) sg[x]^=(sg[to[i]]+1);
		}
	}
	if(vis[x]==1) --Top;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	int T;
	while(scanf("%d",&T)!=EOF){
		int ans=0;
		while(T--){
			int n=read(),m=read();
			memset(Begin,0,sizeof(Begin)),e=0;
			memset(sg,0,sizeof(sg));
			memset(vis,0,sizeof(vis)),Top=0;
			while(m--){
				int x=read(),y=read();
				add_edge(x,y),add_edge(y,x);
			}
			dfs(1,0);
			ans^=sg[1];
		}
		if(ans) printf("Sally\n");
		else printf("Harry\n");
	}
	return 0;
}
