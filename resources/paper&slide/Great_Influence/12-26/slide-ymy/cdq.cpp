#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define For(i,a,b) for(i=(a);i<=(b);++i)
using namespace std;
const int MAXN=100010;
template<typename T>
inline void read(T &x)
{
    T s=0,f=1;
    char k=getchar();
    while(!isdigit(k)&&k!='-')k=getchar();
    if(!isdigit(k))
    {
        f=-1;
        k=getchar();
    }
    while(isdigit(k))
    {
        s=(s<<3)+(s<<1)+(k^48);
        k=getchar();
    }
    x=f*s;
}
int n,m,e,ans[MAXN],tree[10000010];
struct node
{
    int a,b,c,cnt,ans;
    node()
    {
        cnt=ans=0;
    }
    friend bool operator==(node a,node b)
    {
        return !(a.a^b.a)&&!(a.b^b.b)&&!(a.c^b.c);
    }
}p[MAXN];
bool cmp2(node a,node b)
{
    if(a.b^b.b)return a.b<b.b;
    return a.c<b.c;
}
bool cmp1(node a,node b)
{
    if(a.a^b.a)return a.a<b.a;
    return cmp2(a,b);
}
int lowbit(int x)
{
    return x&-x;
}
void add(int a,int b)
{
    while(a<=m)
    {
        tree[a]+=b;
        a+=lowbit(a);
    }
}
int query(int a)
{
    int ans=0;
    while(a)
    {
        ans+=tree[a];
        a-=lowbit(a);
    }
    return ans;
}
void cdq(int l,int r)
{
    if(l==r)return;
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    sort(p+l,p+mid+1,cmp2);
    sort(p+mid+1,p+r+1,cmp2);
    int i=l,j=mid+1;
    while(j<=r)
    {
        while(i<=mid&&p[i].b<=p[j].b)
        {
            add(p[i].c,p[i].cnt);
            ++i;
        }
        p[j].ans+=query(p[j].c);
        ++j;
    }
    For(j,l,i-1)add(p[j].c,-p[j].cnt);
}
int main()
{
    read(n);
    read(m);
    int i;
    For(i,1,n)
    {
        read(p[i].a);
        read(p[i].b);
        read(p[i].c);
        p[i].cnt=1;
    }
    sort(p+1,p+n+1,cmp1);
    For(i,1,n)
    {
        int k=i+1;
        while(p[k]==p[i])++k;
        --k;
        p[i].cnt+=k-i;
        p[++e]=p[i];
        i=k;
    }
    cdq(1,e);
    For(i,1,e)ans[p[i].ans+p[i].cnt-1]+=p[i].cnt;
    //For(i,1,e)cout<<p[i].a<<' '<<p[i].b<<' '<<p[i].c<<' '<<p[i].ans<<endl;
    //putchar('\n');
    For(i,0,n-1)printf("%d\n",ans[i]);
    return 0;
}

