#include<map>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define getchar getchar_unlocked
#define mem(a,b) memset(a,b,sizeof a)
#define  For(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define rFor(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
using namespace std;
typedef long long LL;
const int N=200010;
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
LL ans;
int n,tot,lst;
int Link[N],Max[N];
map<int,int>s[N];
inline void init(){tot = lst = 1;}
void extend(int x)
{
    int p,np,q,nq;
    Max[ np = ++tot ] = Max[ p = lst ]+1;
    for(;p && !s[p][x];p = Link[p])
        s[p][x] = np;
    if(!p)Link[np] = 1;
    else
    {
        q = s[p][x];
        if(Max[q] == Max[p]+1)Link[np] = q;
        else
        {
            Max[ nq = ++tot ] = Max[p]+1;
            s[nq] = s[q];
            Link[nq] = Link[q];
            Link[np] = Link[q] = nq;
            for(;p && s[p][x] == q;p = Link[p])
                s[p][x] = nq;
        }
    }
    lst = np;
}
int main()
{
    init();
    int x;
    read(n);
    For(_,1,n)
    {
        read(x);
        extend(x);
        ans += Max[lst] - Max[Link[lst]];
        printf("%lld\n",ans);
    }
    return 0;
}
?
