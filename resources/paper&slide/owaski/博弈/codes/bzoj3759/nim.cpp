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
const int maxn=100+10;
int a[maxn],p[maxn];
int main(){
#ifndef ONLINE_JUDGE
    freopen("nim.in","r",stdin);
    freopen("nim.out","w",stdout);
#endif
    int T=read();
    while(T--){
        int n=read();
        bool flag=0;
        memset(p,0,sizeof(p));
        REP(i,1,n){
            int x=read();
            if(flag) continue;
            DREP(j,29,0) if(x&(1<<j)){
                if(!p[j]){p[j]=x;break;}
                else x^=p[j];
            }
            if(!x) flag=1;
        }
        if(flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
