#include<bits/stdc++.h>
#define For(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define Fordown(i,r,l) for(int i=(r),i##end=(l);i>=i##end;i--)
using namespace std;
typedef long long ll;
const int INF=1e9;
const double Pi=acos(-1.0);
const int N=(1<<23)+10;
const int M=1500+10;
struct Cplx{
	double re,im;
}A[N],B[N];
int r[N],C[M<<1][M<<1],vis[M<<1][M<<1];
char str[N];
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
	freopen("LOJ6388.in","r",stdin);
	freopen("LOJ6388.out","w",stdout);
#endif
	int n=read(),m=read(),k=read();
	int cnt=0;
	for(Lim=1;Lim<=(n*m<<1);Lim<<=1)cnt++;
	For(i,0,Lim-1)r[i]=r[i>>1]>>1 | (i & 1)<<(cnt-1);
	cnt=0;
	For(i,1,n){
		scanf("%s",str+1);
		For(j,1,m)A[cnt++].re=str[j]-'0';
	}
	scanf("%s",str+1);
	int Lx,Ly,Rx,Ry,x,y;
	Lx=Ly=Rx=Ry=x=y=1500;vis[x][y]=1;
	For(i,1,k){
		if(str[i]=='w')x--;
		if(str[i]=='a')y--;
		if(str[i]=='s')x++;
		if(str[i]=='d')y++;
		vis[x][y]=1;
		Lx=min(x,Lx),Ly=min(y,Ly),Rx=max(x,Rx),Ry=max(y,Ry);
	}
	For(i,Lx,Rx)For(j,Ly,Ry)C[i-Lx+1][j-Ly+1]=vis[i][j];
	cnt=0;
	For(i,1,n)For(j,1,m)B[cnt++].re=C[i][j];
	reverse(B,B+cnt);
	FFT(A,1),FFT(B,1);
	For(i,0,Lim-1)A[i]=A[i]*B[i];
	FFT(A,-1);
	int ans=0;
	For(i,0,n-(Rx-Lx)-1)For(j,0,m-(Ry-Ly)-1)if(1.0*A[n*m-1+i*m+j].re/Lim<0.5)ans++;
	printf("%d\n",ans);
	return 0;
}
