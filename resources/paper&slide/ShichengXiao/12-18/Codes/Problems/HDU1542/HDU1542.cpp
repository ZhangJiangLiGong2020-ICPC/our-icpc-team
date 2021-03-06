#include<bits/stdc++.h>
#define For(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define Fordown(i,r,l) for(int i=(r),i##end=(l);i>=i##end;i--)
using namespace std;
typedef long long ll;
const int INF=1e9;
const int N=2e2+10;
struct Seg{
	double l,r,h;int val;
	bool operator < (const Seg &rhs) const {
		return h<rhs.h;
	}
}a[N];
double pos[N],sum[N<<2];
inline int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch) && ch!='-')ch=getchar();
	if(ch=='-')flag=-1,ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*flag;
}
struct Seg_T{
#define mid ((l+r)>>1)
	int cnt[N<<2];
	inline void Push_Up(int h,int l,int r){
		if(cnt[h])sum[h]=pos[r+1]-pos[l];
		else if(l==r)sum[h]=0;
		else sum[h]=sum[h<<1]+sum[h<<1|1];
	}
	inline void Modify(int h,int l,int r,int L,int R,int val){
		if(L<=l && r<=R){
			cnt[h]+=val,Push_Up(h,l,r);
			return;
		}
		if(L<=mid)Modify(h<<1,l,mid,L,R,val);
		if(R>mid)Modify(h<<1|1,mid+1,r,L,R,val);
		Push_Up(h,l,r);
	}
}T;
int main(){
#ifndef ONLINE_JUDGE
	freopen("HDU1542.in","r",stdin);
	freopen("HDU1542.out","w",stdout);
#endif
	int Case=0,n;
	while(scanf("%d",&n)==1){
		if(!n)break;
		For(i,1,n){
			double x1,x2,y1,y2;
			scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2);
			a[i]=(Seg){x1,x2,y1,1};
			a[i+n]=(Seg){x1,x2,y2,-1};
			pos[i]=x1,pos[i+n]=x2;
		}
		n<<=1;
		sort(a+1,a+n+1),sort(pos+1,pos+n+1);
		int cnt=unique(pos+1,pos+n+1)-pos-1;
		double ans=0;
		For(i,1,n){
			int l=lower_bound(pos+1,pos+cnt+1,a[i].l)-pos;
			int r=lower_bound(pos+1,pos+cnt+1,a[i].r)-pos;
			if(l<r)T.Modify(1,1,cnt,l,r-1,a[i].val);
			ans+=sum[1]*(a[i+1].h-a[i].h);
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n", ++Case, ans);
	}
	return 0;
}
