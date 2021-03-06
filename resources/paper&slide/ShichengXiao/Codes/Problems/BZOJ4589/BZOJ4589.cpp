#include<bits/stdc++.h>
#define For(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define Fordown(i,r,l) for(int i=(r),i##end=(l);i>=i##end;i--)
using namespace std;
typedef long long ll;
const int INF=1e9;
const int M=5e5+10;
const int Lim=65536+10;
const int mod=1e9+7,Inv=5e8+4;
int prime[M],vis[M],A[Lim],B[Lim];
inline int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch) && ch!='-')ch=getchar();
	if(ch=='-')flag=-1,ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*flag;
}
inline void init(int n){
	int cnt=0;vis[1]=1;
	For(i,2,n){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt && i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i % prime[j]==0)break;
		}
	}
}
inline int Mod(int val){
	if(val >= mod)val-=mod;
	if(val < 0)val+=mod;
	return val;
}
inline void FWT(int P[],bool flag,int Len){
	for(int i=2;i<=Len;i<<=1)
		for(int j=0;j<Len;j+=i)
			For(k,0,(i>>1)-1){
				int x=P[j+k],y=P[j+k+(i>>1)];
				if(flag==1)P[j+k]=Mod(x+y),P[j+k+(i>>1)]=Mod(x-y);
				else P[j+k]=1ll*(x+y)*Inv%mod,P[j+k+(i>>1)]=1ll*Mod(x-y)*Inv%mod;
			}
}
inline void fpm(int Pw,int Len){
	B[0]=1;
	FWT(A,1,Len),FWT(B,1,Len);
	while(Pw){
		if(Pw & 1)For(i,0,Len-1)B[i]=1ll*A[i]*B[i]%mod;
		For(i,0,Len-1)A[i]=1ll*A[i]*A[i]%mod;Pw/=2;
	}
	FWT(B,0,Len);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("BZOJ4589.in","r",stdin);
	freopen("BZOJ4589.out","w",stdout);
#endif
	init(M-5);
	int n,m;
	while(scanf("%d%d",&n,&m)==2){
		memset(A,0,sizeof(A)),memset(B,0,sizeof(B));
		For(i,1,m)if(!vis[i])A[i]=1;
		int Len;
		for(Len=1;Len<=m;Len<<=1);
		fpm(n,Len);
		printf("%d\n",B[0]);
	}
	return 0;
}
