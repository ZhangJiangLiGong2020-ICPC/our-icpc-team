#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define mem(a,b) memset(a,b,sizeof a)
#define  For(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define rFor(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
using namespace std;
typedef long long LL;
const int N=1000010;
template<typename T>inline T chkmax(T _A,T _B){return _A>_B?_A:_B;}
template<typename T>inline T chkmin(T _A,T _B){return _A<_B?_A:_B;}
template<typename T>void read(T&x)
{
    x=0;int _f=0;char ch=getchar();
    while(!isdigit(ch))_f|=(ch=='-'),ch=getchar();
    while( isdigit(ch))x=x*10+ch-'0',ch=getchar();
    x=_f?-x:x;
}
inline void file()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
}
int n,tot,lst;
LL ans,w[N],f[N],Max[N];
int Link[N],s[N][26];
int S[N],topo[N];
char str[N];
inline void init(){tot=lst=1;}
void extend(int x)
{
    int p,np,q,nq;
    Max[np=++tot]=Max[p=lst]+1;
    w[np]=f[np]=1;
    for(;p&&!s[p][x];p=Link[p])
        s[p][x]=np;
    if(!p)
        Link[np]=1;
    else
    {
        q=s[p][x];
        if(Max[q]==Max[p]+1)
            Link[np]=q;
        else
        {
            Max[nq=++tot]=Max[p]+1;
            memcpy(s[nq],s[q],sizeof(s[q]));
            Link[nq]=Link[q];
            Link[np]=Link[q]=nq;
            for(;p&&s[p][x]==q;p=Link[p])
                s[p][x]=nq;
        }
    }
    lst=np;
}
void Radix_Sort()
{
    For(i,1,tot)S[Max[i]]++;
    For(i,1,n)S[i]+=S[i-1];
    rFor(i,tot,1)topo[S[Max[i]]--]=i;
    rFor(i,tot,1)f[Link[topo[i]]]+=f[topo[i]];
}
void solve()
{
    For(i,1,tot)
    {
        ans-=Max[Link[i]]*f[i]*w[Link[i]];
        w[Link[i]]+=f[i];
    }
    ans*=2;
}
int main()
{
    file();
    init();
    scanf("%s",str);
    n=strlen(str);
    rFor(i,n-1,0)extend(str[i]-'a');
    Radix_Sort();
    solve();
    For(i,1,n)ans+=(LL)i*(n-1);
    printf("%lld\n",ans);
    return 0;
}
?
