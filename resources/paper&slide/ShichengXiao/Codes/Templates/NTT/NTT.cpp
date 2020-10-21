#include<bits/stdc++.h>
#define For(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define Fordown(i,r,l) for(int i=(r),i##end=(l);i>=i##end;i--)
using namespace std;
typedef long long ll;
const int INF=1e9;
const int N=262144+10;
const int mod=998244353;
const int G0=3;
int A[N],B[N],r[N],G[20][2],Gn[N];
int Lim;
inline int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch) && ch!='-')ch=getchar();
	if(ch=='-')flag=-1,ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*flag;
}
inline int fpm(int a,int b){
	int res=1;
	while(b){
		if(b & 1)res=1ll*res*a%mod;
		a=1ll*a*a%mod,b/=2;
	}
	return res;
}
inline int Mod(int val){
	if(val >= mod)val-=mod;
	if(val < 0)val+=mod;
	return val;
}
inline void NTT(int P[],bool opt){
	For(i,0,Lim-1)if(i<r[i])swap(P[i],P[r[i]]);
	int cnt=1;
	for(int i=2;i<=Lim;i<<=1,cnt++){
		Gn[0]=1;
		For(j,1,(i>>1)-1)Gn[j]=1ll*Gn[j-1]*G[cnt][opt]%mod;
		for(int j=0;j<Lim;j+=i)
			For(k,0,(i>>1)-1){
				int u=P[j+k],v=1ll*P[j+k+(i>>1)]*Gn[k]%mod;
				P[j+k]=Mod(u+v),P[j+k+(i>>1)]=Mod(u-v);
			}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("NTT.in","r",stdin);
	freopen("NTT.out","w",stdout);
#endif
	int n=read(),m=read(),cnt=0;
	For(i,0,n)A[i]=read();
	For(i,0,m)B[i]=read();
	for(Lim=1;Lim<=n+m;Lim<<=1)cnt++;
	For(i,0,Lim-1)r[i]=r[i>>1]>>1 | (i & 1)<<(cnt-1);
	cnt=0;
	for(int i=1;i<=Lim;i<<=1,cnt++){
		G[cnt][1]=fpm(G0,(mod-1)/i);
		G[cnt][0]=fpm(G[cnt][1],mod-2);
	}
	NTT(A,1),NTT(B,1);
	For(i,0,Lim)A[i]=1ll*A[i]*B[i]%mod;
	NTT(A,0);
	int Inv=fpm(Lim,mod-2);
	For(i,0,n+m)printf("%lld%c",1ll*A[i]*Inv%mod,i==n+m?'\n':' ');
	return 0;
}
