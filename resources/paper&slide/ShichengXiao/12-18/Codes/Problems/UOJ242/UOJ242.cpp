#include<bits/stdc++.h>
#define For(i,l,r) for(int i=(l),i##end=(r);i<=i##end;i++)
#define Fordown(i,r,l) for(int i=(r),i##end=(l);i>=i##end;i--)
using namespace std;
typedef long long ll;
const int INF=1e9;
const double eps=1e-12;
const double Pi=acos(-1.0);
inline int read(){
	int x=0,flag=1;
	char ch=getchar();
	while(!isdigit(ch) && ch!='-')ch=getchar();
	if(ch=='-')flag=-1,ch=getchar();
	while(isdigit(ch))x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*flag;
}
namespace Geometry{
	inline int dcmp(double val){
		if(abs(val) < eps)return 0;
		else return val > 0 ? 1 : -1;
	}
	struct Point{
		double x,y;
		Point(double a=0,double b=0):x(a),y(b){}
	};
	struct Circle{
		Point O;double r;
		Circle(Point a=Point(0,0),double b=0):O(a),r(b){}
		Point point(double rad){
			return Point(O.x+cos(rad)*r,O.y+sin(rad)*r);
		}
	};
	typedef Point Vector;
	Vector operator + (const Vector &A,const Vector &B){
		return Vector(A.x+B.x,A.y+B.y);
	}
	Vector operator - (const Vector &A,const Vector &B){
		return Vector(A.x-B.x,A.y-B.y);
	}
	Vector operator * (const Vector &A,const double &p){
		return Vector(A.x*p,A.y*p);
	}
	Vector operator / (const Vector &A,const double &p){
		return Vector(A.x/p,A.y/p);
	}
	bool operator == (const Vector &A,const Vector &B){
		return !dcmp(A.x-B.x) && !dcmp(A.y-B.y);
	}
	bool operator < (const Vector &A,const Vector &B){
		return dcmp(A.x-B.x)<0 || (!dcmp(A.x-B.x) && A.y<B.y);
	}
	Vector Rotate(Vector A,double rad){
		return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
	}
	double Dot(Vector A,Vector B){
		return A.x*B.x+A.y*B.y;
	}
	double Cross(Vector A,Vector B){
		return A.x*B.y-A.y*B.x;
	}
	double Length(Vector A){
		return sqrt(Dot(A,A));
	}
	double Angle(Vector A,Vector B){ //Angle_Between_Two_Vectors
		return acos(Dot(A,B)/Length(A)/Length(B));
	}
	double Angle(Vector A){ //Angle_of_a_Vector
		return atan2(A.y,A.x);
	}
	double DisTL(Point P,Point A,Point B){ //Distance_to_Line
		return fabs(Cross(P-A,B-A))/Length(B-A);
	}
	double DisTS(Point P,Point A,Point B){ //Distance_to_Segment
		if(A==B)return Length(P-A);
		Vector V1=B-A,V2=P-A,V3=P-B;
		if(dcmp(Dot(V1,V2))<0) return Length(V2);
		else if(dcmp(Dot(V1,V3))>0) return Length(V3);
		else return abs(Cross(V1,V2)/Length(V1));
	}
	Point LP(Point P,Point A,Point B){ //Line_Projection 点在直线上的投影
		Vector V=B-A;
		return A+V*(Dot(V,P-A)/Dot(V,V));
	}
	//此处以及下方两个函数直线的表达方式，是用一个点和一个从这个点出发的向量来表示的。
	Point LI(Point A,Vector P,Point B,Vector Q){ //Line_Intersection
		Vector V=A-B;
		return A+P*Cross(Q,V)/Cross(P,Q);
	}
	//下面的两个判断函数均允许线段在端点处相交
	bool IsLSI(Point A,Vector P,Point B,Vector Q){ //Is_Line_and_Segment_Has_Intersection
		Vector V1=B-A,V2=B+Q-A;
		return dcmp(Cross(P,V1))!=dcmp(Cross(P,V2));
	}
	bool IsSSI(Point A,Vector P,Point B,Vector Q){ //Is_Segment_and_another_Segment_Has_Intersection
		return IsLSI(A,P,B,Q) && IsLSI(B,Q,A,P);
	}
	bool IsPoS(Point P,Point A,Point B){ //Is_Point_on_Segment
		if(A.x>B.x)swap(A,B);
		if(P.x<A.x || P.x>B.x || dcmp((B.y-A.y)/(B.x-A.x)-(B.y-P.y)/(B.x-P.x)))return 0;
		else return 1;
	}
	bool IsPiP(Point P,Point Poly[],int n){ //Is_Point_in_Polygon
		int wn=0;
		For(i,1,n){
			Point A=Poly[i],B=Poly[i%n+1];
			if(IsPoS(P,A,B))return -1;
			int k=dcmp(Cross(B-A,P-A)),d1=dcmp(A.y-P.y),d2=dcmp(B.y-P.y);
			if(k>0 && d1<=0 && d2>0)++wn;
			if(k<0 && d2<=0 && d1>0)--wn;
		}
		if(wn)return 1;else return 0;
	}
	int CLI(Circle C,Point A,Point B,Point &P1,Point &P2){ //Circle_Line_Intersection
		double Dis=DisTL(C.O,A,B);
		int flag=dcmp(Dis-C.r);
		if(flag>0)return 0;
		Point P=LP(C.O,A,B);
		if(!flag){
			P1=P2=P;return 1;
		}
		double L=sqrt(C.r*C.r+Dis*Dis);
		Vector V=(B-A)/Length(B-A);
		P1=P-V*L,P2=P+V*L;return 2;
	}
	int CI(Circle C1,Circle C2,Point &P1,Point &P2){ //Circle_Intersection 返回值为-1表示两圆重合，有无穷个交点
		double Dis=Length(C1.O-C2.O);
		if(!dcmp(Dis)){ //同心圆
			if(!dcmp(C1.r-C2.r))return -1;
			else return 0;
		}
		if(dcmp(C1.r+C2.r-Dis)<0 || dcmp(abs(C1.r-C2.r)-Dis)>0)return 0; //外离与内含
		double Base=Angle(C2.O-C1.O),Ang=acos((C1.r*C1.r+Dis*Dis-C2.r*C2.r)/(2*C1.r*Dis));
		P1=C1.point(Base-Ang),P2=C1.point(Base+Ang);
		if(P1==P2)return 1;else return 2;
	}
	int Tg(Point P,Circle C,Point &P1,Point &P2){ //TangentLine_Trough_Point P1/P2是两个切点
		double Dis=Length(C.O-P);
		if(dcmp(Dis-C.r)<0)return 0;
		double Base=Angle(P-C.O),Ang=acos(C.r/Dis);
		P1=C.point(Base-Ang),P2=C.point(Base+Ang);
		if(P1==P2)return 1;else return 2;
	}
	int Tg(Circle C1,Circle C2,Point a[],Point b[]){ //TangentLine_Between_Two_Circles 返回值为-1表示两圆重合，有无穷条公切线；a[]/b[]分别表示在圆C1和圆C2上的切点
		int cnt=0;
		if(C1.r<C2.r)swap(C1,C2),swap(a,b);
		int Dis=Length(C1.O-C2.O),diff=C1.r-C2.r,sum=C1.r+C2.r;
		if(dcmp(Dis-diff)<0)return 0; //内含
		if(!dcmp(Dis) && !dcmp(diff))return -1; //重合
		double Base=Angle(C2.O-C1.O);
		if(!dcmp(Dis-diff)){ //内切
			a[++cnt]=C1.point(Base),b[cnt]=a[cnt];
			return 1;
		}
		//外公切线
		double Ang=acos(diff/Dis);
		a[++cnt]=C1.point(Base+Ang),b[cnt]=C2.point(Base+Ang);
		a[++cnt]=C1.point(Base-Ang),b[cnt]=C2.point(Base-Ang);
		//内公切线
		if(!dcmp(Dis-sum))a[++cnt]=C1.point(Base),b[cnt]=a[cnt]; //外切
		else if(dcmp(Dis-sum)){ //外离
			Ang=acos(sum/Dis);
			a[++cnt]=C1.point(Base+Ang),b[cnt]=C2.point(Pi+Base+Ang);
			a[++cnt]=C1.point(Base-Ang),b[cnt]=C2.point(Pi+Base-Ang);
		}
		return cnt;
	}
	double PA(Point Poly[],int n){ //Polygon_Area
		double S=0;
		For(i,2,n-1)S+=Cross(Poly[i]-Poly[1],Poly[i+1]-Poly[1]);
		return abs(S/2);
	}
}
using namespace Geometry;
const int N=1e5+10;
inline double Correct(double Ang){
	if(Ang<0)Ang+=2*Pi;
	return Ang;
}
struct Line{
	Point P;Vector V;double ang;
	Line(Point a=Point(0,0),Vector b=Vector(0,0)):P(a),V(b){ ang=Correct(Angle(V)); }
};
bool OnLeft(Line L,Point P){
	return Cross(L.V,P-L.P)>0;
}
int id[N];
Line L[N],A;
Point P[N];
multiset <double> Set;
multiset <double>::iterator it1,it2,it;
bool cmp(const int x,const int y){
	return P[x]<P[y];
}
inline bool check(double val){
	if(val<0)val+=2*Pi;
	if(val>Pi-eps)return 1;
	else return 0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("UOJ242.in","r",stdin);
	freopen("UOJ242.out","w",stdout);
#endif
	int n=read();
	int x1,x2,y1,y2;
	For(i,1,n){
		x1=read(),y1=read(),x2=read(),y2=read();
		L[i]=Line(Point(x1,y1),Vector(x2-x1,y2-y1));
	}
	x1=read(),y1=read(),x2=read(),y2=read();
	if(x1>x2)swap(x1,x2),swap(y1,y2);
	A=Line(Point(x1,y1),Vector(x2-x1,y2-y1));
	For(i,1,n)P[i]=LI(L[i].P,L[i].V,A.P,A.V),id[i]=i;
	sort(id+1,id+n+1,cmp);
	For(i,1,n){
		double ang=L[i].ang-A.ang;
		if(ang<0)ang+=2*Pi;
		if(ang-Pi<=0){
			L[i].ang+=Pi;
			if(L[i].ang>=2*Pi)L[i].ang-=2*Pi;
		}
		Set.insert(L[i].ang);
	}
	int flag=1;
	putchar(48);
	double ang,ang1,ang2,delta,delta1,delta2;
	For(i,1,n){
		it1=it2=it=Set.lower_bound(L[id[i]].ang);
		if(it1==Set.begin())it1=Set.end();it1--;
		++it2;if(it2==Set.end())it2=Set.begin();
		ang=*it,ang1=*it1,ang2=*it2;
		delta1=ang-ang1,delta2=ang2-ang,delta=ang2-ang1;
		flag=flag-check(delta1)-check(delta2)+check(delta);
		Set.erase(it);
		L[id[i]].ang+=Pi;
		if(L[id[i]].ang>=2*Pi)L[id[i]].ang-=2*Pi;
		Set.insert(L[id[i]].ang);
		it1=it2=it=Set.lower_bound(L[id[i]].ang);
		if(it1==Set.begin())it1=Set.end();it1--;
		++it2;if(it2==Set.end())it2=Set.begin();
		ang=*it,ang1=*it1,ang2=*it2;
		delta1=ang-ang1,delta2=ang2-ang,delta=ang2-ang1;
		flag=flag+check(delta1)+check(delta2)-check(delta);
		putchar(flag?'0':'1');
	}
	puts("");
	return 0;
}
