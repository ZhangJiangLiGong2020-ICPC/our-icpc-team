#include<bits/stdc++.h>
#define For(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define Fordown(i,r,l) for(int i=(r),i##end=(l);i>=i##end;i--)
using namespace std;
typedef long long ll;
const int INF=1e9;
const double Pi=acos(-1.0);
const int N=262144+10;
struct Cplx{
	double re,im;
}A[N],B[N];
int r[N];
int Lim;
inline Cplx operator + (const Cplx &lhs,const Cplx &rhs){
	return (Cplx){lhs.re+rhs.re,lhs.im+rhs.im};
}
inline Cplx operator - (const Cplx &lhs,const Cplx &rhs){
	return (Cplx){lhs.re-rhs.re,lhs.im-rhs.im};
}
inline Cplx operator * (const Cplx &lhs,const Cplx &rhs){
	return (Cplx){lhs.re*rhs.re-lhs.im*rhs.im,lhs.re*rhs.im+lhs.im*rhs.re};
}
inline int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch) && ch!='-')ch=getchar();
	if(ch=='-')flag=-1,ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*flag;
}
inline void FFT(Cplx P[],int opt){
	For(i,0,Lim-1)if(i<r[i])swap(P[i],P[r[i]]);
	for(int i=2;i<=Lim;i<<=1){
		Cplx Wi=(Cplx){cos(2*Pi/i),opt*sin(2*Pi/i)};
		for(int j=0;j<Lim;j+=i){
			Cplx x=(Cplx){1,0};
			For(k,0,(i>>1)-1){
				Cplx u=P[j+k],v=x*P[j+k+(i>>1)];
				P[j+k]=u+v,P[j+k+(i>>1)]=u-v;
				x=x*Wi;
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("FFT.in","r",stdin);
	freopen("FFT.out","w",stdout);
#endif
	int n=read(),m=read(),cnt=0;
	For(i,0,n)A[i].re=read();
	For(i,0,m)B[i].re=read();
	for(Lim=1;Lim<=n+m;Lim<<=1)cnt++;
	For(i,0,Lim-1)r[i]=r[i>>1]>>1 | (i & 1)<<(cnt-1);
	FFT(A,1),FFT(B,1);
	For(i,0,Lim-1)A[i]=A[i]*B[i];
	FFT(A,-1);
	For(i,0,n+m)printf("%d%c",(int)(A[i].re*1.0/Lim+0.5),i==n+m?'\n':' ');
	return 0;
}
