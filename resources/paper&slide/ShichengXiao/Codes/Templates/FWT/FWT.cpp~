#include<bits/stdc++.h>
#define For(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define Fordown(i,r,l) for(int i=(r),i##end=(l);i>=i##end;i--)
using namespace std;
typedef long long ll;
const int INF=1e9;
const int Lim=131072+10;
const int mod=1e9+7,Inv=5e8+4;
int A[Lim],B[Lim];
inline int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch) && ch!='-')ch=getchar();
	if(ch=='-')flag=-1,ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*flag;
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
				if(flag==1){
//					Xor : P[j+k]=Mod(x+y),P[j+k+(i>>1)]=Mod(x-y);
//					Or : P[j+k]=Mod(x+y);
//					And : P[j+k+(i>>1)]=Mod(x+y);
				}
				else{
//					Xor : P[j+k]=1ll*(x+y)*Inv%mod,P[j+k+(i>>1)]=1ll*Mod(x-y)*Inv%mod;
//					Or : P[j+k]=Mod(x-y);
//					And : P[j+k+(i>>1)]=Mod(y-x);
				}
			}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("FWT.in","r",stdin);
	freopen("FWT.out","w",stdout);
#endif
	int n=read();
	For(i,0,n)A[i]=read();
	For(i,0,n)B[i]=read();
	int Len;
	for(Len=1;Len<=n+n;Len<<=1);
	FWT(A,1,Len),FWT(B,1,Len);
	For(i,0,Len-1)A[i]=1ll*A[i]*B[i]%mod;
	FWT(A,0,Len);
	For(i,0,n<<1)printf("%d%c",A[i],i==iend?'\n':' ');
	return 0;
}
