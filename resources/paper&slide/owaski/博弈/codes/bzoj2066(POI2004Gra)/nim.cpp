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
const int maxn=1e6+10;
int a[maxn],b[maxn],tmp;
int main(){
#ifndef ONLINE_JUDGE
    freopen("nim.in","r",stdin);
    freopen("nim.out","w",stdout);
#endif
    int m=read(),n=read(),ans=0;
    REP(i,1,n) a[i]=read();
    if(a[n]==m-1){
        int i=n-1;
        while(i && a[i]==a[i+1]-1) --i;
        printf("%d\n",n-i);return 0;
    }
    REP(i,1,n){
        a[i]=m-2-a[i]-(n-i);
        if(!a[i]) continue;
        if(i==1 || a[tmp]>a[i]) a[++tmp]=a[i];
        ++b[tmp];
    }
    int cnt=0;
    REP(i,1,tmp) if(a[i]&1) ans^=b[i];
    REP(i,1,tmp)
        if(a[i]&1) cnt+=((ans^b[i])<b[i]);
        else{
            int u=b[i+1];if(a[i]!=a[i+1]+1) u=0;
            cnt+=((ans^u)>u && (ans^u)<=u+b[i]);
        }
    printf("%d\n",cnt);
    return 0;
}
