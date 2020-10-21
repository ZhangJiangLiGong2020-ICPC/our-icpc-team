#include<bits/stdc++.h>
using namespace std;
#define REP(i,st,ed) for(register int i=st,i##end=ed;i<=i##end;++i)
#define DREP(i,st,ed) for(register int i=st,i##end=ed;i>=i##end;--i)
typedef long long ll;
inline int read(){
	int x;
	char c;
	int f=1;
	while((c=getchar())!='-' && (c<'0' || c>'9'));
	if(c=='-') c=getchar(),f=-1;
	x=c^'0';
	while((c=getchar())>='0' && c<='9') x=(x<<1)+(x<<3)+(c^'0');
	return x*f;
}
inline ll readll(){
	ll x;
	char c;
	ll f=1;
	while((c=getchar())!='-' && (c<'0' || c>'9'));
	if(c=='-') c=getchar(),f=-1;
	x=c^'0';
	while((c=getchar())>='0' && c<='9') x=(x<<1ll)+(x<<3ll)+(c^'0');
	return x*f;
}
const int maxn=1e5+10;
int main(){
	int n=read(),ans=0;
	REP(i,1,n){
		int x=read(),y=read();
		while(x%y!=0){
			int r=(x/y)*y;
			x-=(x/y+1)*max((x-r)/(x/y+1),1);
			if(x<y) break;
		}
		ans^=x/y;
	}
	if(ans) printf("Takahashi\n");
	else printf("Aoki\n");
	return 0;
}
