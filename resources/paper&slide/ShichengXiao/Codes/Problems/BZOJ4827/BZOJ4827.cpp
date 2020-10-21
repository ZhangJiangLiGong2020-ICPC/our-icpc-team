#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=2e9;
const long double eps=1e-9;
const double Pi=acos(-1.0);
const int maxn=2e5+10;
struct Complex{
	double re,im;
};
Complex operator + (const Complex &lhs,const Complex &rhs){
	return (Complex){lhs.re+rhs.re,lhs.im+rhs.im};
}
Complex operator - (const Complex &lhs,const Complex &rhs){
	return (Complex){lhs.re-rhs.re,lhs.im-rhs.im};
}
Complex operator * (const Complex &lhs,const Complex &rhs){
	return (Complex){lhs.re*rhs.re-lhs.im*rhs.im,lhs.re*rhs.im+lhs.im*rhs.re};
}
struct Complex A[maxn],B[maxn];
int a[maxn],b[maxn],r[maxn],ans[maxn];
int n;
inline int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch) && ch!='-')ch=getchar();
	if(ch=='-')flag=-1,ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*flag;
}
inline void FFT(Complex P[],int opt){
	int i,j,k;
	for(i=0;i<n;i++)if(i<r[i])swap(P[i],P[r[i]]);
	for(i=2;i<=n;i<<=1){
		Complex Wi=(Complex){cos(2*Pi/i),opt*sin(2*Pi/i)};
		int p=i/2;
		for(j=0;j<n;j+=i){
			Complex x=(Complex){1,0};
			for(k=0;k<p;k++,x=x*Wi){
				Complex u=P[j+k],v=x*P[j+k+p];
				P[j+k]=u+v;
				P[j+k+p]=u-v;
			}
		}
	}
}
int main(){
	int i,j,k,m,tmp;
#ifndef ONLINE_JUDGE
	freopen("BZOJ4827.in","r",stdin);
	freopen("BZOJ4827.out","w",stdout);
#endif
	n=read();m=read();
	tmp=n;
	int finalans=0,sum1=0,sum2=0,flag=1;
	for(i=1;i<=n;i++)a[i]=read(),sum1+=a[i];
	for(i=1;i<=n;i++)b[i]=read(),sum2+=b[i];
	if(sum1>sum2)swap(sum1,sum2),flag=-1;
	int delta=(sum2-sum1)/n+((sum2-sum1)%n>n/2);
	delta*=flag;
	if(delta>=0)for(i=1;i<=n;i++)a[i]+=delta;
	else for(i=1;i<=n;i++)b[i]-=delta;
	for(i=1;i<=n;i++)A[i-1].re=a[i],B[i-1].re=b[n-i+1],finalans+=a[i]*a[i]+b[i]*b[i];
	int cnt=0;k=n+n;
	for(n=1;n<=k;n<<=1)cnt++;
	for(i=1;i<=n;i++)r[i]=(r[i>>1]>>1) | ((i & 1) * (1<<(cnt-1)));
	FFT(A,1);FFT(B,1);
	for(i=0;i<n;i++)A[i]=A[i]*B[i];
	FFT(A,-1);
	for(i=0;i<n;i++)ans[i]=floor(1.0*A[i].re/n+0.5);
	swap(tmp,n);
	int maxans=0;
	for(i=0;i<=n;i++)
		maxans=max(maxans,ans[i]+ans[i+n]);
	printf("%d\n",finalans-2*maxans);
	return 0;
}
