#define ONLINE_JUDGE
#include<bits/stdc++.h>
using namespace std;
const int Log = 20;
const int maxn = 600050;
const int Len = maxn * 3;
const int alp = 256;
const int block = 250;
int r[Len], sa[Len];
int wa[Len], wb[Len];
int wv[Len], ss[Len];
#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : tb ) )
#define G(x) ((x) < tb ? (x) * 3 + 1 : ((x) - tb ) * 3 + 2 )
bool c0( int *r, int a, int b ) {
	return r[a] == r[b] and r[a + 1] == r[b + 1] and	r[a + 2] == r[b + 2];
}
bool c12( int k, int *r, int a, int b ) {
	if( k == 2 ) return r[a] < r[b] or r[a] == r[b] and c12( 1, r, a + 1, b + 1 );
	return r[a] < r[b] or r[a] == r[b] and wv[a + 1] < wv[b + 1];
}
void sort( int *r, int *a, int *b, int n, int m ) {
	for( int i = 0; i < n; i ++ ) wv[i] = r[a[i]];
	for( int i = 0; i < m; i ++ ) ss[i] = 0;
	for( int i = 0; i < n; i ++ ) ss[wv[i]]++;
	for( int i = 1; i < m; i ++ ) ss[i] += ss[i - 1];
	for( int i = n - 1; i >= 0; i-- ) 
		b[--ss[wv[i]]] = a[i];
}
void DC3( int *r, int *sa, int n, int m ) {
	int i, j, p;
	int *san = sa + n, *rn = r + n;
	int ta = 0, tb = ( n + 1 ) / 3, tbc = 0;
	r[n] = r[n + 1] = 0;
	for( i = 0; i < n; i ++ ) 
		if( i % 3 != 0 ) wa[tbc++] = i;
	sort( r + 2, wa, wb, tbc, m );
	sort( r + 1, wb, wa, tbc, m );
	sort( r, wa, wb, tbc, m );
	for( p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i ++ )
		rn[F(wb[i])] = c0( r, wb[i - 1], wb[i] ) ? p - 1 : p ++;
	if( p < tbc ) DC3( rn, san, tbc, p );
	else for( i = 0; i < tbc; i ++ ) san[rn[i]] = i;
	for( i = 0; i < tbc; i ++ ) if( san[i] < tb ) wb[ta++] = san[i] * 3;
	if( n % 3 == 1 ) wb[ta++] = n - 1;
	sort( r, wb, wa, ta, m );
	for( i = 0; i < tbc; i ++ ) wv[wb[i] = G(san[i])] = i;
	for( i = 0, j = 0, p = 0; i < ta and j < tbc; p ++ )
		sa[p] = c12( wb[j] % 3, r, wa[i], wb[j] ) ? wa[i ++] : wb[j++];
	for( ; i < ta; p++ ) sa[p] = wa[i++];
	for( ; j < tbc; p++ ) sa[p] = wb[j++];
}
int rk[maxn], lcp[maxn];
void Lcp( int *r, int *sa, int n ) {
	lcp[0] = 0;
	for( int i = 0; i < n; i ++ ) rk[sa[i]] = i;
	for( int h = 0, i = 0; i < n; i ++ ) 
	if( rk[i] ) {
		int j = sa[rk[i] - 1];
		while( r[i + h] == r[j + h] ) h ++;
		lcp[rk[i]] = h;
		if( h > 0 ) h--;
	}
}
char s[maxn];
int pos[maxn];
int a[maxn], cnt[maxn];
int lo[Log+1][maxn];
int hi[Log+1][maxn];
void init_RMQ( int n ) {
	for( int i = 1; i <= n; i ++ ) 
		lo[0][i] = lcp[i];
	for( int i = 1; i <= Log; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			int k = j - ( 1 << ( i - 1 ) );
			if( k <= 0 ) lo[i][j] = 0;
			else lo[i][j] = min( lo[i-1][j], lo[i-1][k] );
		}
	}
	for( int i = 1; i <= n; i ++ ) hi[0][i] = lcp[i+1];
	for( int i = 1; i <= Log; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			int k = j + ( 1 << ( i - 1 ) );
			if ( k > n ) hi[i][j] = 0;
			else hi[i][j] = min( hi[i-1][j], hi[i-1][k] );
		}
	}
}
struct query {
	int L, R, pL, pR, id;
	query( int _L = 0, int _R = 0, int _pL = 0, 
	int _pR = 0, int _id = 0 ) : L(_L), R(_R), pL(_pL),
	pR(_pR), id(_id) {}
	bool operator < ( const query &q ) const {
		int i = ( pL + block - 1 ) / block, j = ( q.pL + block - 1 ) / block;
		if( i != j ) return i < j;
		return pR < q.pR;
	}
} q[maxn];
struct RLT {
	int x, y;
	RLT( int _x = 0, int _y = 0 ) : x(_x), y(_y) {}
	bool operator < ( const RLT &p ) const {
		return y != p.y ? y > p.y : x < p.x;
	}
} rlt[maxn];
template< class T >
inline bool chkmin( T &a, T b ) {
	if( b < a ) { a = b; return true; }
	return false;
}
class RMQ_Tree {
private :
	int n;
	RLT Min[maxn<<1];
public:
	void build( int m ) {
		Min[n = m] = RLT( n, 0 );
		for( int i = 1; i <= n; i ++ )
		 	Min[i + n] = RLT( i, 0 );
		for( int i = n - 1; i; i -- ) 
			Min[i] = min( Min[i << 1], Min[i<<1|1] );
	}
	void modify( int p, RLT v ) {
		Min[p += n] = v;
		for( ; p > 1; p >>= 1 )
			Min[p >> 1] = min( Min[p], Min[p^1] );
	}
	RLT queryMin( int L, int R ) {
		RLT rlt = RLT( -1, -1 );
		for( L += n, R += n; L <= R; L = ( L + 1 ) >> 1,
		R = ( R - 1 ) >> 1 ) {
		 	if( L & 1 ) chkmin( rlt, Min[L] );
			if( !(R&1)) chkmin( rlt, Min[R] );
		}
		return rlt;
	}
} T;
int inv[maxn];
void poke( int u ) {
	int id = pos[sa[a[u]]];
	cnt[id] += inv[u] ? -1 : 1;
	inv[u] ^= 1;
	T.modify( id, RLT( id, cnt[id] ));
}
int main() {
	scanf("%s", s);
	int len = 0, n, m;
	int sn = strlen( s );
	for( int i = 0; i < sn; i ++ ) r[len++] = s[i];
	r[len++] = alp;
	scanf("%d", &n);
	for( int i = 1; i <= n; i ++ ) {
		scanf("%s", s);
		for( int j = 0; s[j]; j ++ ) {
			pos[len] = i;
			r[len++] = s[j];
		}
		r[len++] = alp + i;
	}
	DC3( r, sa, len + 1, n + 266 );
	Lcp( r, sa, len + 1 );
	init_RMQ( len );
	int tot = 0;
	for( int i = 0; i < len; i ++ )
		if( pos[sa[i]] ) a[++tot] = i;
	scanf("%d", &m);
	for( int i = 1; i <= m; i ++ ) {
		int L, R, x, y;
		scanf("%d%d%d%d", &L, &R, &x, &y );
		int p = rk[x-1], pL = p, pR = p;
		for( int j = Log; j >= 0; j -- ) {
			if( lo[j][pL] >= y-x+1 ) pL -= ( 1 << j );
			if( hi[j][pR] >= y-x+1 ) pR += ( 1 << j );
		}
		pL = lower_bound( a+1, a + tot + 1, pL ) - a;
		pR = upper_bound( a+1, a + tot + 1, pR ) - a - 1;
		q[i] = query( L, R, pL, pR, i );
	}
	sort( q+1, q+m+1 );
	T.build( n );
	int curL = 1, curR = 0;
	for( int i = 1; i <= m; i ++ ) {
		while( curR < q[i].pR ) poke( ++curR );
		while( curL > q[i].pL ) poke( --curL );
		while( curR > q[i].pR ) poke( curR-- );
		while( curL < q[i].pL ) poke( curL++ );
		rlt[q[i].id] = T.queryMin( q[i].L, q[i].R );
	}
	for( int i = 1; i <= m; i ++ )
		printf("%d %d\n", rlt[i].x, rlt[i].y );
	return 0;
}	
