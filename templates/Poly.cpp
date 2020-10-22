#include<cstdio>
#include<iostream>
#include<cstdlib>
#define f(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;i=-(~i))
#define fe(i,a,b) for(register int i=(a),i##end=(b);i<i##end;i=-(~i))
#define rf(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;i=~(-i))
const int neko=100010,feko=400010,mod=998244353;
int n,a[neko],fac[neko],ifac[neko];
int grt[60][2];
typedef int arr[feko];
arr A,B,X,F,E,rev,gp;
int ADD(int x,int y){return (x+=y)>=mod?x-mod:x;}
int spow(int m,int n)
{
	int b=1;
	for(;n;n>>=1,m=1ll*m*m%mod)if(n&1)b=1ll*b*m%mod;
	return b;
}
namespace Conv
{
	using std::swap;
	const int gen=3,igen=spow(3,mod-2);
	void NTT(int *p,int n,int opt)
	{
		fe(i,0,n)if(i<rev[i])swap(p[i],p[rev[i]]);
		int hfi,u,v;
		for(int i=2,cnt=1;i<=n;i<<=1,++cnt)
		{
			hfi=i>>1;
			fe(j,1,hfi)gp[j]=1ll*gp[j-1]*grt[cnt][opt]%mod;
			for(int j=0;j<n;j+=i)
				fe(k,0,hfi)
				{
					u=p[j+k],v=1ll*p[j+k+hfi]*gp[k]%mod;
					p[j+k]=ADD(u,v),p[j+k+hfi]=ADD(u,mod-v);
				}
		}
		if(!opt)
		{
			int in=spow(n,mod-2);
			fe(i,0,n)p[i]=1ll*p[i]*in%mod;
		}
	}
	void getrev(int n,int cnt)
	{fe(i,0,n)rev[i]=(rev[i>>1]>>1)|((i&1)<<cnt);}
	void init(int n)
	{gp[0]=1;for(int i=2,cnt=1;i<=n;i<<=1,++cnt)grt[cnt][1]=spow(gen,(mod-1)/i),grt[cnt][0]=spow(igen,(mod-1)/i);}
}
namespace Poly
{
	using namespace Conv;
	void Inv(int len,int *C,int *X)//len是长度！
	{
		if(len==1){X[0]=spow(C[0],mod-2);return;}
		Inv(len+1>>1,C,X);
		int n,cnt;
		for(n=1,cnt=0;n<(len<<1);n<<=1)++cnt;--cnt;//长度一定不大于len<<1
		fe(i,0,len)A[i]=C[i];fe(i,len,n)A[i]=0;//A在这个模意义下！
		getrev(n,cnt);
		NTT(A,n,1),NTT(X,n,1);
		fe(i,0,n)X[i]=ADD(2ll*X[i]%mod,mod-1ll*A[i]*X[i]%mod*X[i]%mod);
		NTT(X,n,0);
		fe(i,len,n)X[i]=0;
	}
	void Int(int n,int *C)
	{rf(i,n,1)C[i]=1ll*C[i-1]*fac[i-1]%mod*ifac[i]%mod;C[0]=0;}
	void Der(int n,int *C)
	{fe(i,0,n-1)C[i]=1ll*C[i+1]*(i+1)%mod;C[n]=0;}
	void Ln(int len,int *C)
	{
		Inv(len,C,X),Der(len,C);
		int n,cnt;
		for(n=1,cnt=0;n<(len<<1);n<<=1)++cnt;--cnt;
		getrev(n,cnt);
		NTT(C,n,1),NTT(X,n,1);
		fe(i,0,n)C[i]=1ll*C[i]*X[i]%mod,X[i]=0;
		NTT(C,n,0);
		fe(i,len,n)C[i]=0;
		Int(len,C);
	}
	void Exp(int len,int *C,int *E)
	{
		if(len==1){E[0]=1;return;}
		Exp(len+1>>1,C,E);
		int n,cnt;
		for(n=1,cnt=0;n<(len<<1);n<<=1)++cnt;--cnt;
		getrev(n,cnt);
		fe(i,0,len)F[i]=E[i];Ln(len,F);
		fe(i,0,len)A[i]=ADD(mod-F[i],C[i]);A[0]=ADD(A[0],1);fe(i,len,n)A[i]=0;
		NTT(A,n,1),NTT(E,n,1);
		fe(i,0,n)E[i]=1ll*E[i]*A[i]%mod;
		NTT(E,n,0);
		fe(i,len,n)E[i]=0;
	}
}
int main()
{
	using namespace Poly;
	scanf("%d",&n),--n;
	int x,cnt=0;
	for(x=2;x<(n<<1|1);x<<=1);Conv::init(x);
	f(i,0,n)scanf("%d",&a[i]);
	Inv(n+1,a,X);
	Exp(n+1,a,E);
	f(i,0,n)printf("%d%c",X[i],i^iend?' ':'\n');
	return 0;
}
