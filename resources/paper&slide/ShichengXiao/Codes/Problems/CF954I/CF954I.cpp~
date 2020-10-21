#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=1e9;
const long double eps=1e-9;
const double Pi=acos(-1.0);
const int maxn=125000+10;
char a[maxn],b[maxn];
struct Complex{
	double re,im;
}A[maxn<<2],B[maxn<<2];
int ans[maxn<<2][6][6],r[maxn<<2],fa[6];
int N;
inline Complex operator + (const Complex &lhs,const Complex &rhs){
	return (Complex){lhs.re+rhs.re,lhs.im+rhs.im};
}
inline Complex operator - (const Complex &lhs,const Complex &rhs){
	return (Complex){lhs.re-rhs.re,lhs.im-rhs.im};
}
inline Complex operator * (const Complex &lhs,const Complex &rhs){
	return (Complex){lhs.re*rhs.re-lhs.im*rhs.im,lhs.re*rhs.im+lhs.im*rhs.re};
}
inline int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch) && ch!='-')ch=getchar();
	if(ch=='-')flag=-1,ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*flag;
}
int find(int x){
	return fa[x]==x ? x : fa[x]=find(fa[x]);
}
inline void FFT(Complex P[],int opt){
	int i,j,k;
	for(i=0;i<N;i++)if(i<r[i])swap(P[i],P[r[i]]);
	for(i=2;i<=N;i<<=1){
		int p=i/2;
		Complex Wi=(Complex){cos(2*Pi/i),opt*sin(2*Pi/i)};
		for(j=0;j<N;j+=i){
			Complex x=(Complex){1,0};
			for(k=0;k<p;k++,x=x*Wi){
				Complex u=P[j+k],v=x*P[j+k+p];				
				P[j+k]=u+v;P[j+k+p]=u-v;
			}
		}
	}
}
int main(){
	int i,j,k,m,n;
#ifndef ONLINE_JUDGE
	freopen("CF954I.in","r",stdin);
	freopen("CF954I.out","w",stdout);
#endif
	scanf("%s",a);scanf("%s",b);
	n=strlen(a),m=strlen(b);
	int tot=n+m,cnt=0;
	for(N=1;N<=tot;N<<=1)cnt++;
	for(i=0;i<N;i++)r[i]=r[i>>1]>>1 | ((i & 1)*(1<<(cnt-1)));
	for(i=0;i<=5;i++)
		for(j=0;j<=5;j++){
			memset(A,0,sizeof(A));memset(B,0,sizeof(B));
			for(k=0;k<n;k++)if(a[k]=='a'+i)A[k].re=1;
			for(k=0;k<m;k++)if(b[m-k-1]=='a'+j)B[k].re=1;
			FFT(A,1),FFT(B,1);
			for(k=0;k<N;k++)A[k]=A[k]*B[k];
			FFT(A,-1);
			for(k=0;k<N;k++)ans[k][i][j]=(int)(A[k].re/N+0.5);
		}
	for(i=m-1;i<n;i++){
		for(j=0;j<=5;j++)fa[j]=j;
		for(j=0;j<=5;j++)
			for(k=j+1;k<=5;k++)
				if(ans[i][j][k] || ans[i][k][j]){
					int u=find(j),v=find(k);
					if(u==v)continue;
					fa[u]=v;
				}
		int res=0;
		for(j=0;j<=5;j++)if(fa[j]!=j)res++;
		printf("%d%c",res,i==n-1?'\n':' ');
	}
	return 0;
}
