#include<bits/stdc++.h>
#define For(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define Fordown(i,r,l) for(int i=(r),i##end=(l);i>=i##end;i--)
using namespace std;
typedef long long ll;
const int INF=1e9;
const int N=262144+10;
const int Lim=1e5+5;
const int mod=998244353,G0=3;
int a[N],b[N],r[N],A[N],B[N],G[20][2],Gn[N],fac[N];
inline int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch) && ch!='-')ch=getchar();
	if(ch=='-')flag=-1,ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*flag;
}
inline int fpm(int bs,int Pw){
	int res=1;
	while(Pw){
		if(Pw & 1)res=1ll*res*bs%mod;
		bs=1ll*bs*bs%mod,Pw/=2;
	}
	return res;
}
inline int Mod(int val){
	if(val >= mod)val-=mod;
	if(val < 0)val+=mod;
	return val;
}
inline void init(int n){
	fac[0]=1;
	For(i,1,n)fac[i]=1ll*fac[i-1]*i%mod;
}
inline void NTT(int P[],int Len,int opt){
	int cnt=0;
	for(int res=1;res<Len;res<<=1)cnt++;
	For(i,0,Len-1)r[i]=r[i>>1]>>1 | (i & 1)<<(cnt-1);
	For(i,0,Len-1)if(i<r[i])swap(P[i],P[r[i]]);
	cnt=1;
	for(int i=2;i<=Len;i<<=1,cnt++){
		Gn[0]=1;
		For(j,1,(i>>1)-1)Gn[j]=1ll*Gn[j-1]*G[cnt][opt]%mod;
		for(int j=0;j<Len;j+=i)
			For(k,0,(i>>1)-1){
				int u=P[j+k],v=1ll*Gn[k]*P[j+k+(i>>1)]%mod;
				P[j+k]=Mod(u+v),P[j+k+(i>>1)]=Mod(u-v);
			}
	}
}
inline void CDQ(int L,int R){
	if(L==R)return;
	int mid=(L+R)>>1,Len=R-L+1;
	CDQ(L,mid);
	For(i,0,mid-L)A[i]=b[i+L];
	For(i,0,Len-1)B[i]=a[i+1];
	NTT(A,Len<<1,1),NTT(B,Len<<1,1);
	For(i,0,(Len<<1)-1)A[i]=1ll*A[i]*B[i]%mod;
	NTT(A,Len<<1,0);
	int Inv=fpm(Len<<1,mod-2);
	For(i,mid+1,R)b[i]=Mod(b[i]-1ll*A[i-L-1]*Inv%mod);
	For(i,0,(Len<<1)-1)A[i]=B[i]=0;
	CDQ(mid+1,R);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("51Nod1514.in","r",stdin);
	freopen("51Nod1514.out","w",stdout);
#endif
	init(Lim+5);
	For(i,0,Lim)a[i]=b[i]=fac[i];
	int n;
	for(n=1;n<=Lim;n<<=1);
	for(int cnt=0,i=1;i<=(n<<1);i<<=1,cnt++){
		G[cnt][1]=fpm(G0,(mod-1)/i);
		G[cnt][0]=fpm(G[cnt][1],mod-2);
	}
	CDQ(1,n);
	int T=read();
	while(T--){
		n=read();
		printf("%d\n",b[n]);
	}
	return 0;
}
