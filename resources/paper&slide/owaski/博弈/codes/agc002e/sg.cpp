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
const int maxn=1e5+10;
int a[maxn];
int main(){
	int n=read();
	REP(i,1,n) a[i]=read();
	sort(a+1,a+n+1,greater<int>());
	bool ans=0;
	REP(i,1,n) if(i+1>a[i+1]){
		int j=i+1;
		while(j<=n && a[j]==i) ans^=1,++j;
		ans|=(a[i]-i)&1;
		break;
	}
	if(ans) printf("First\n");
	else printf("Second\n");
	return 0;
}
