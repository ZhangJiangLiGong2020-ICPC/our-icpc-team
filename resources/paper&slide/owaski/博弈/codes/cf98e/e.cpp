#include<bits/stdc++.h>
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
const int maxn=1000+10;
double dp[maxn][maxn];
bool vis[maxn][maxn];
double f(int n,int m){
	if(m<=0) return 1;
	if(n==0) return 1.0/(m+1);
	if(vis[n][m]) return dp[n][m];
	double p=f(m,n-1)/(1.0/(m+1)+f(m,n-1));
	vis[n][m]=1;
	return dp[n][m]=p*m*1.0/(m+1)*(1-f(m-1,n))+(1-p);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("e.in","r",stdin);
	freopen("e.out","w",stdout);
#endif
	int n=read(),m=read();
	double x=f(n,m);
	printf("%.10lf %.10lf\n",x,1-x);
	return 0;
}
