#include<bits/stdc++.h>
#define For(i,l,r) for(int i = (l),i##end = (r);i <= i##end;i++)
#define Fordown(i,r,l) for(int i = (r),i##end = (l);i >= i##end;i--)
#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long ll;

template <typename T> inline bool chkmin(T &x,T y) { return y < x ? x = y,1 : 0; }
template <typename T> inline bool chkmax(T &x,T y) { return x < y ? x = y,1 : 0; }

const int INF = 0x3f3f3f3f;
const int N = 1e5 + 10;

int sta[N];

inline int read() {
	int x = 0,flag = 1;
	char ch = getchar();
	while(!isdigit(ch) && ch != '-') ch = getchar();
	if(ch == '-') flag = -1,ch = getchar();
	while(isdigit(ch)) x = (x << 3) + (x << 1) + (ch - '0'),ch = getchar();
	return x * flag;
}

struct Point {
	ll x,y;
	Point(ll a = 0,ll b = 0) : x(a),y(b) {}
} A[N],B[N],res[N << 1];
typedef Point Vector;
Vector operator + (const Vector &a,const Vector &b) {
	return Vector(a.x + b.x,a.y + b.y);
}
Vector operator - (const Vector &a,const Vector &b) {
	return Vector(a.x - b.x,a.y - b.y);
}
ll Cross(Vector a,Vector b) {
	return a.x * b.y - a.y * b.x;
}
ll Poly_Area(Point Poly[],int n) {
	ll S = 0;
	For(i,2,n - 1) S += Cross(Poly[i] - Poly[1],Poly[i + 1] - Poly[1]);
	return abs(S);
}
inline bool cmp_pos(const Point &lhs,const Point &rhs) {
	return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
}
inline bool cmp_angle(const Point &lhs,const Point &rhs) {
	return atan2(lhs.y,lhs.x) < atan2(rhs.y,rhs.x);
}

inline int Convex_Hull(Point P[],int n,int cnt) {
	sort(P + 1,P + n + 1,cmp_pos);
	int top = 1;
	sta[top] = 1;
	For(i,2,n) {
		while(top > 1 && Cross(P[sta[top]] - P[sta[top - 1]],P[i] - P[sta[top - 1]]) <= 0) top--;
		sta[++top] = i;
	}
	int cur = top;
	Fordown(i,n - 1,1) {
		while(top > cur && Cross(P[sta[top]] - P[sta[top - 1]],P[i] - P[sta[top - 1]]) <= 0) top--;
		sta[++top] = i;
	}
	For(i,2,top) res[++cnt] = P[sta[i]] - P[sta[i - 1]];
	return cnt;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("tsinsen1279.in","r",stdin);
	freopen("tsinsen1279.out","w",stdout);
#endif

	int n = read(),m = read(),tot = 0;
	For(i,1,n) {
		int x = read(),y = read();
		A[i] = Point(x,y);
	}
	For(i,1,m) {
		int x = read(),y = read();
		B[i] = Point(x,y);
	}
	tot = Convex_Hull(A,n,0),tot = Convex_Hull(B,m,tot);
	sort(res + 1,res + tot + 1,cmp_angle);
	For(i,1,tot) res[i] = res[i] + res[i - 1];
	printf("%lld\n",Poly_Area(res,tot));

	return 0;
}
