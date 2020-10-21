#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define For(i,a,b) for(i=(a),i<=(b);++i)
#define Forward(i,a,b) for(i=(a),i>=(b);--i)
#define Chkmin(a,b) a=a<b?a:b
#define Chkmax(a,b) a=a>b?a:b
#define pb push_back

inline void read(int &x)
{
    static const int BUFSIZE = 1048576;
    static char buf[BUFSIZE];
    static char *bufnow = buf;
    static char *bufmax = buf;
    if (bufnow == bufmax) {
        bufmax = buf + fread(buf, 1, BUFSIZE, stdin);
        bufnow = buf;
    }
    static int c;
    c = *bufnow++;
    for (;!isdigit(c);c = *bufnow++) {
            if (bufnow == bufmax) {
            bufmax = buf + fread(buf, 1, BUFSIZE, stdin);
            bufnow = buf;
        }
    }
    x = 0;
    for (;isdigit(c);c = *bufnow++) {
        x = (x << 1) + (x << 3) + c - 48;
        if (bufnow == bufmax) {
            bufmax = buf + fread(buf, 1, BUFSIZE, stdin);
            bufnow = buf;
        }
    }
}

inline void write(int a,char ed='\n')
{
    static short s[13],tp;
    if(!a){putchar('0'),putchar(ed);return;}
    for(tp=0;a;a/=10)s[++tp]=a%10;
    for(;tp;putchar(s[tp--]^48));
    putchar(ed);
}
using namespace std;
void file()
{
#ifndef ONLINE_JUDGE
    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
#endif
}

const int MAXN=6e5+7;

static int n,m;

namespace Kdtree
{
    static struct poi
    {
        int x,y;
    }p[MAXN],sta[MAXN];
    static int son[MAXN][2],sz[MAXN],e,tp,rt,Di[MAXN],num[MAXN];
    
    const double alp=0.75;

    inline bool cmpx(poi x,poi y){return x.x<y.x;}

    inline bool cmpy(poi x,poi y){return x.y<y.y;}

    static int inx[MAXN],axx[MAXN],iny[MAXN],axy[MAXN];

    inline void pushup(int x)
    {
        static int l,r;l=son[x][0],r=son[x][1];
        sz[x]=sz[l]+sz[r]+1;
        inx[x]=axx[x]=p[x].x;iny[x]=axy[x]=p[x].y;
        if(l)Chkmin(inx[x],inx[l]),Chkmax(axx[x],axx[l]),
            Chkmin(iny[x],iny[l]),Chkmax(axy[x],axy[l]);
        if(r)Chkmin(inx[x],inx[r]),Chkmax(axx[x],axx[r]),
            Chkmin(iny[x],iny[r]),Chkmax(axy[x],axy[r]);
    }

    int make_tree(int l,int r)
    {
        if(l>r)return 0;
        if(l==r){Di[num[l]]=0;p[num[l]]=sta[l];
            pushup(num[l]);return num[l];}
        static int ax,ay,ix,iy;ax=ay=0;ix=iy=1e7;
        Rep(i,l,r)Chkmax(ax,sta[i].x),Chkmax(ay,sta[i].y)
            ,Chkmin(ix,sta[i].x),Chkmin(iy,sta[i].y);
        int mid=(l+r)>>1;
        if(ax-ix>=ay-iy)nth_element(sta+l,sta+mid+1,sta+r+1,cmpx),Di[num[mid]]=0;
        else nth_element(sta+l,sta+mid+1,sta+r+1,cmpy),Di[num[mid]]=1;
        p[num[mid]]=sta[mid];
        son[num[mid]][0]=make_tree(l,mid-1);
        son[num[mid]][1]=make_tree(mid+1,r);
        pushup(num[mid]);
        return num[mid];
    }

    void distroy(int x)
    {
        if(son[x][0])distroy(son[x][0]);
        sta[++tp]=p[x],num[tp]=x;son[x][0]=0;
        if(son[x][1])distroy(son[x][1]);
        son[x][1]=0;
    }

    inline void insert(int x,int y)
    {
        static int now,f,dir;
        now=rt;f=0;
        while(now)
        {
            ++sz[now];
            Chkmax(axx[now],x);Chkmin(inx[now],x);
            Chkmax(axy[now],y);Chkmin(iny[now],y);
            dir=!(!Di[now]&&x<=p[now].x||Di[now]&&y<=p[now].y);
            if(!son[now][dir]){son[now][dir]=++e,p[e]=(poi){x,y};
                pushup(e);return;}
            else if(sz[son[now][dir]]+1>sz[now]*alp)
            {
                tp=0;distroy(now);sta[++tp]=(poi){x,y};num[tp]=++e;
                if(now==rt)rt=make_tree(1,tp);
                else son[f][now==son[f][1]]=make_tree(1,tp),pushup(f);
                return;
            }
            else f=now,now=son[now][dir];
        }
    }

    static int an;

    inline int dist(int po,int x,int y)
    {
        return max(0,x-axx[po])+max(0,inx[po]-x)
            +max(0,y-axy[po])+max(0,iny[po]-y);
    }

    void quer(int now,int x,int y)
    {
        Chkmin(an,abs(p[now].x-x)+abs(p[now].y-y));
        int dl,dr;
        dl=son[now][0]?dist(son[now][0],x,y):1e8;
        dr=son[now][1]?dist(son[now][1],x,y):1e8;
        if(dl<dr)
        {
            if(dl<an)quer(son[now][0],x,y);
            if(dr<an)quer(son[now][1],x,y);
        }
        else
        {
            if(dr<an)quer(son[now][1],x,y);
            if(dl<an)quer(son[now][0],x,y);
        }
    }
}
using namespace Kdtree;

inline void init()
{
    read(n);read(m);
    Rep(i,1,n)read(sta[i].x),read(sta[i].y),num[i]=i;tp=e=n;
    rt=make_tree(1,tp);
}

inline void solve()
{
    static int opt,x,y;
    Rep(i,1,m)
    {
        read(opt);read(x);read(y);
        if(opt==1)insert(x,y);
        else an=1e8,quer(rt,x,y),write(an,'\n');
    }
}

int main()
{
	file();
    init();
    solve();
    return 0;
}
