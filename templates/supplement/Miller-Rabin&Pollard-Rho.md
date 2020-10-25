## Miller-Rabin&Pollard-Rho

背板子

[洛谷P4718 【模板】Pollard-Rho算法](https://www.luogu.org/problemnew/show/P4718)

辣鸡卡常题，参考了一下讨论版里的卡常技巧

upd:模数为`long long`级别的乘法取模原理

如果NOI能用什么`__int128`的话倒还好说

但是别忘了`long double`和`__int128`的位长是一样的啊！因此用它做`long long`级别的运算的精度损失是完全可以接受的。

我们知道$$a*b\bmod p=a*b-\lfloor\frac{a*b}p\rfloor*p$$

然后我们用`long double`先除后乘，考虑浮点数除法会丢掉小数点后面一个很小的值，而之后强制转换整形是要强制舍去的，所以要加一个eps。
```cpp
#include<bits/stdc++.h>
#define LL long long
#define RG register
#define R RG int
using namespace std;
LL t,n,ans;
inline LL Mul(LL a,LL b,LL p){//㧟的玄学乘法取模
    LL d=((long double)a/p*b+1e-8);
    LL r=a*b-d*p;
    return r<0?r+p:r;
}
inline LL Gcd(LL a,LL b){//㧟的builtin辗转相减
    if(!a||!b)return a|b;
    int t=__builtin_ctzll(a|b);
    a>>=__builtin_ctzll(a);
    do{
        b>>=__builtin_ctzll(b);
        if(a>b)swap(a,b);
        b-=a;
    }while(b);
    return a<<t;
}
inline LL Qpow(LL b,LL k,LL p,LL a=1){
    for(;k;k>>=1,b=Mul(b,b,p))
        if(k&1ll)a=Mul(a,b,p);
    return a;
}
inline LL MR(LL n){
    if(n==2)return 1;
    if(n==1||(1&n)==0)return 0;
    static int a[]={2,3,7,13,61,24251};
    LL u=n-1,x,y;R k=0;
    while((1&u)==0)u>>=1,++k;
    for(R i=0;i<6&&a[i]<n;++i){
        x=Qpow(a[i],u,n);
        for(R j=0;j<k;++j,x=y){
            y=Mul(x,x,n);
            if(y==1&&x!=1&&x!=n-1)return 0;
        }
        if(x!=1)return 0;
    }
    return 1;
}
inline LL F(LL a,LL c,LL n){
    LL t=Mul(a,a,n)+c;
    return t<n?t:t-n;
}
inline LL PR(LL n){
    if((1&n)==0)return 2;
    LL c=rand(),a=rand(),b=a,g;
    do{
        a=F(a,c,n);b=F(F(b,c,n),c,n);
        g=Gcd(n,abs(a-b));
        if(g!=1&&g!=n)return g;
    }while(a!=b);
    return g;
}
void find(LL n){
    if(n==1||n<=ans)return;
    if(MR(n)){ans=max(ans,n);return;}
    LL d=n;
    while(d==n)d=PR(n);
    while(n%d==0)n/=d;
    find(n);find(d);
}
int main(){
    srand(time(NULL));
    cin>>t;
    while(t--){
        cin>>n;ans=1;find(n);
        if(ans==n)puts("Prime");
        else cout<<ans<<'\n';
    }
    return 0;
}
```
