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
int lim;
int n,f[maxn],g[maxn];
bool p[maxn];
int a[maxn];
inline int sg(int x){
    if(x>lim) return f[n/x];
    return g[x];
}
void init(){
    for(int i=1,r;i<=n;i=r+1){
        r=n/(n/i);int tmp=0,res=0;
        for(int j=2,r1;j<=r;j=r1+1){
            r1=r/(r/j);
            int t=sg(r/j);tmp^=t;
            p[tmp]=1;
            a[++res]=tmp;
            if((r1-j)&1) tmp^=t;
        }
        int t=1;
        while(p[t]) ++t;
        if(i>lim) f[n/i]=t;
        else g[i]=t;
        REP(i,1,res) p[a[i]]=0;
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("sg.in","r",stdin);
    freopen("sg.out","w",stdout);
#endif
    n=read();
    lim=(int)sqrt(n);
    int T=read();
    init();
//  REP(i,1,n) cout<<i<<' '<<sg(n/i)<<endl;
    while(T--){
        int ans=0,m=read();
        REP(i,1,m){
            int x=read();x=n/x;
            ans^=sg(x);
        }
        if(ans) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
