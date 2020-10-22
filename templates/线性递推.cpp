#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define f(i,a,b) for(register int i=(a);i<=(b);i=-(~i))
#define fe(i,a,b) for(register int i=(a);i<(b);i=-(~i))
const int keko=32010,feko=600010,mod=998244353;
int n,k,a[keko],f[keko],gpow[1010][2],ans;
typedef int arr[feko];
arr C,X,G,F,rev,A,B,Hr,Qr,gi;
//C:c序列 F:特征多项式 G:转移矩阵系数 X:逆元
int ADD(int x,int y)
{return (x+=y)>=mod?x-mod:x;}
int cmin(int x,int y){return x<y?x:y;}
int spow(int m,int n)
{
    int b=1;
    for(;n;n>>=1,m=1ll*m*m%mod)if(n&1)b=1ll*b*m%mod;
    return b;
}
namespace Conv
{
    using std::swap;
    int m,n;
    const int gen=3,igen=spow(3,mod-2);
    void NTT(int *p,int opt)
    {
        fe(i,0,n)if(i<rev[i])swap(p[i],p[rev[i]]);
        int hfi,u,v;
        for(register int i=2,tp=1;i<=n;i<<=1,++tp)
        {
            hfi=i>>1;
            fe(j,1,hfi)gi[j]=1ll*gi[j-1]*gpow[tp][opt]%mod;
            for(register int j=0;j<n;j+=i)
            {
                fe(k,0,hfi)
                {
                    u=p[j+k],v=1ll*gi[k]*p[j+k+hfi]%mod;
                    p[j+k]=ADD(u,v),p[j+k+hfi]=ADD(u,mod-v);
                }
            }
        }
        if(!opt)
        {
            int in=spow(n,mod-2);
            fe(i,0,n)p[i]=1ll*p[i]*in%mod;
        }
    }
    int solve(int n1,int n2,int opt)
    {
        m=n1+n2;int cnt=0;
        for(n=1;n<=m;n<<=1)++cnt;--cnt;
        if(~cnt)fe(i,0,n)rev[i]=(rev[i>>1]>>1)|((i&1)<<cnt);
        //printf("%d %d\n",opt,n);
        NTT(A,1),NTT(B,1);
        if(opt==1)fe(i,0,n)A[i]=1ll*A[i]*B[i]%mod;
        else fe(i,0,n)A[i]=1ll*A[i]*B[i]%mod*B[i]%mod;
        NTT(A,0);
        return n;
    }
    void init(int n)
    {gi[0]=1;for(register int i=2,tp=1;i<=n;i<<=1,++tp)gpow[tp][1]=spow(gen,(mod-1)/i),gpow[tp][0]=spow(igen,(mod-1)/i);}
}
namespace Poly
{
    using std::reverse;
    using namespace Conv;
    int flag=0;
    void Mul(int n,int m,int *C,int nx)
    {
        int Cn=solve(n,m,1);
        f(i,0,nx)C[i]=A[i],A[i]=B[i]=0;
        f(i,nx+1,Cn)A[i]=B[i]=0;
    }
    void Inv(int *C,int n)
    {
        int len=2;X[0]=spow(C[0],mod-2);
        while(len<=n)
        {
            fe(i,0,len>>1)A[i]=C[i],B[i]=X[i];
            solve((len>>1)-1,len-1,2);
            fe(i,0,len)X[i]=ADD(ADD(X[i],X[i]),mod-A[i]);
            fe(i,len,len<<1)A[i]=B[i]=0;
            len<<=1;
        }f(i,0,len)A[i]=B[i]=0;
    }
    void Div(int *H,int *Q,int n,int m)//H=WQ+P
    {
        if(n<m)return;
        memcpy(Hr,H,sizeof Hr);
        reverse(Hr,Hr+n+1);
        f(i,n-m+1,n)Hr[i]=0;
        //printf("%d\n",n);
        /*puts("orz?");
        f(i,0,x)printf("%d ",X[i]);
        putchar('\n');*/
        f(i,0,n-m)A[i]=Hr[i],B[i]=X[i];
        Mul(n-m,n-m,Hr,n-m);
        reverse(Hr,Hr+n-m+1);
        f(i,0,n-m)A[i]=Hr[i],B[i]=Q[i];
        f(i,n-m+1,m)B[i]=Q[i];
        solve(n-m,m,1);
        fe(i,0,m)H[i]=ADD(H[i],mod-A[i]);
        f(i,m,n)H[i]=0;
        memset(A,0,sizeof A),memset(B,0,sizeof B);
    }
    void Mod(int *C,int *D,int *X,int n)
    {
        fe(i,0,n)A[i]=C[i],B[i]=D[i];
        Mul(n-1,n-1,C,n-1);
        Div(C,X,n,k);
    /*	fe(i,0,k)printf("%d ",C[i]);
        putchar('\n');*/
    }
    void Spow(int *M,int n,int *B,int *X)
    {
        int y;
        y=k<<1;
        for(register int x=1;n;n>>=1,Mod(M,M,X,2<<x),++x)
        {
            if(n&1)Mod(B,M,X,y);
            if((1<<(x-1))>=y)--x;
        }
    }
    void Init(int n,int m)
    {
        memcpy(Qr,F,sizeof Qr);
        reverse(Qr,Qr+m+1);
        int x;
        for(x=2;x<(n-m+1);x<<=1);
        Inv(Qr,x);
    }
}
int main()
{
    scanf("%d%d",&n,&k);
    int x;
    for(x=2;x<=k;x<<=1);
    Conv::init(x<<3);
    //让我们算一笔账：求逆<<2，快速幂的2<<x最大可以到y(k<<1)的两倍，两者都需要再<<1（因为是乘法），于是就<<3(*8)
    f(i,1,k)scanf("%d",&f[i]),F[k-i]=ADD(0,mod-f[i]);
    F[k]=1;
    fe(i,0,k)scanf("%d",&a[i]),a[i]=ADD(a[i],mod);
    G[1]=1,C[0]=1;//实际上是求转移矩阵的系数，也就是我们把转移矩阵设成一个未知数x，它是一次的，系数是1
    Poly::Init(k<<2,k);//只用求一次逆元
    Poly::Spow(G,n,C,F);
    fe(i,0,k)ans=ADD(1ll*C[i]*a[i]%mod,ans);
    return printf("%d\n",ADD(ans,mod)),std::cerr<<clock()*1.0/CLOCKS_PER_SEC<<std::endl,0;
}
