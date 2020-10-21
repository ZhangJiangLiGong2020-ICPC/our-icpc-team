#include<bits/stdc++.h>
#define For(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define Fordown(i,r,l) for(int i=(r),i##end=(l);i>=i##end;i--)
using namespace std;
typedef long long ll;
const int INF=1e9;
const double Pi=acos(-1.0);
const int N=50+10,M=1e2+10,T=2e4+10,MaxLen=65536+10;
struct Cplx{
	double re,im;
}A[MaxLen],B[MaxLen];
double dp[N][T],f[M][T],Pb[M][T],Sum[M][T];
int r[MaxLen];
struct node{
	int id,dis;
	bool operator < (const node &rhs) const {
		return dis>rhs.dis;
	}
};
priority_queue <node> q;
struct G{
	int x,y,z;
}edge[M];
int to[M<<1],nex[M<<1],beg[N],w[M<<1],dis[N],vis[N];
int e,n,m,t,cost;
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
inline void add(int x,int y,int z){
	to[++e]=y,nex[e]=beg[x],beg[x]=e,w[e]=z;
}
inline void FFT(Cplx P[],int Len,int opt){
	int cnt=0;
	for(int res=1;res<Len;res<<=1)cnt++;
	For(i,0,Len-1)r[i]=r[i>>1]>>1 | (i & 1)<<(cnt-1);
	For(i,0,Len-1)if(i<r[i])swap(P[i],P[r[i]]);
	for(int i=2;i<=Len;i<<=1){
		Cplx Wi=(Cplx){cos(2*Pi/i),opt*sin(2*Pi/i)};
		for(int j=0;j<Len;j+=i){
			Cplx x=(Cplx){1,0};
			For(k,0,(i>>1)-1){
				Cplx u=P[j+k],v=x*P[j+k+(i>>1)];
				P[j+k]=u+v,P[j+k+(i>>1)]=u-v;
				x=x*Wi;
			}
		}
	}
	if(opt==-1)For(i,0,Len-1)P[i].re/=Len;
}
inline void CDQ(int L,int R){
	if(L==R){
		For(i,1,m)dp[edge[i].x][L]=min(dp[edge[i].x][L],f[i][L]+edge[i].z);
		return;
	}
	int mid=(L+R)>>1,Len=R-L+1;
	CDQ(mid+1,R);
	For(i,1,m){
		For(j,0,R-L-1)A[j].re=Pb[i][j+1];
		For(j,0,R-mid-1)B[j].re=dp[edge[i].y][mid+j+1];
		reverse(B,B+R-mid);
		int res;
		for(res=1;res<Len;res<<=1);
		FFT(A,res,1),FFT(B,res,1);
		For(j,0,res-1)A[j]=A[j]*B[j];
		FFT(A,res,-1);
		For(j,L,mid)f[i][j]+=A[R-j-1].re;
		For(j,0,res-1)A[j].re=A[j].im=B[j].re=B[j].im=0;
	}
	CDQ(L,mid);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("CF553E.in","r",stdin);
	freopen("CF553E.out","w",stdout);
#endif
	n=read(),m=read(),t=read(),cost=read();
	For(i,1,m){
		int x=read(),y=read(),z=read();
		edge[i]=(G){x,y,z};
		add(y,x,z);
		For(j,1,t)Pb[i][j]=read()/100000.0,Sum[i][j]=Sum[i][j-1]+Pb[i][j];
	}
	memset(dis,63,sizeof(dis));
	dis[n]=0;q.push((node){n,0});
	int sum=1;
	while(!q.empty()){
		node val=q.top();q.pop();
		if(vis[val.id])continue;
		dis[val.id]=val.dis;vis[val.id]=1;sum++;
		for(int i=beg[val.id];i;i=nex[i])
			q.push((node){to[i],dis[val.id]+w[i]});
	}
	For(i,1,n-1)For(j,0,t)dp[i][j]=INF;
	For(i,1,m)For(j,1,t)f[i][j]=(1-Sum[i][t-j])*(dis[edge[i].y]+cost);
	CDQ(0,t);
	printf("%.10lf\n",dp[1][0]);
	return 0;
}
