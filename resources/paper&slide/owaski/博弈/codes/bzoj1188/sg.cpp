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
const int maxn=30;
int f[maxn],a[maxn];
bool p[10000+10];
void init(int n){
    REP(i,1,n){
        memset(p,0,sizeof(p));
        REP(j,1,i-1)
            REP(k,1,j)
                p[f[j]^f[k]]=1;
        REP(j,0,n*n) if(!p[j]){
            f[i]=j;
            break;
        }
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("sg.in","r",stdin);
    freopen("sg.out","w",stdout);
#endif
    init(21);
    int T=read();
    while(T--){
        int sum=0,n=read(),ans=0;
        REP(i,1,n) a[i]=read();
        REP(i,1,n) if(a[i]&1) sum^=f[n-i+1];
        REP(i,1,n) if(a[i])
            REP(j,i+1,n)
                REP(k,j,n)
                    if((sum^f[n-i+1]^f[n-j+1]^f[n-k+1])==0){
                        if(!ans) printf("%d %d %d\n",i-1,j-1,k-1);
                        ++ans;
                    }
        if(!ans) printf("-1 -1 -1\n");
        printf("%d\n",ans);
    }
    return 0;
}
