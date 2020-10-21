#include<iostream>    
#include<cstdio>    
#include<cstring>    
#include<algorithm>    
#include<queue>    
using namespace std;  
const int N=1<<25;  
const int blocksize=20000;  
const int blocknum=N/blocksize*3;    
int n,m;    
int cur;    
char str[N+110],s[100];    
queue<int> q;    
struct node     
{    
    char data[blocksize+111];    
    int len,next;  //记录块中元素的总长度和相邻的下一个块的编号，注意编号不一定是连续的  
}; node a[blocknum+1000];    
int newnode()  //新开一个块
{  
    int temp=q.front(); q.pop(); return temp;  
}  
void delnode(int t)//把需要整个删除的块的编号扔进队列中，相当于内存回收，新开块时只需要从中提取编号  
{  
    q.push(t);  
}  
void find(int &pos,int &now)  //从第一个块开始搜索，搜索位置POS所属的块的编号
{  
    for (now=0;a[now].next!=-1&&pos>a[now].len;now=a[now].next)  pos-=a[now].len;  
}  
void fillnode(int pos,int n,char data[],int next)  
{  
    a[pos].next=next;   a[pos].len=n;  
    memcpy(a[pos].data,data,n); //将data 中前n个元素复制到块pos中 
}  
void split(int pos,int p) // 将块pos从p前面一分为二，使块的长度不超过P
{  
    if (a[pos].len==p) return;  
    int t=newnode();  //定义新块
    fillnode(t,a[pos].len-p,a[pos].data+p,a[pos].next);  
    a[pos].next=t;    a[pos].len=p;  
}  
void maintain(int pos)  //将所有的碎块合并
{  
    int t;  
    for (;pos!=-1;pos=a[pos].next){  
      for(t=a[pos].next;t!=-1&&a[pos].len+a[t].len<blocksize;t=a[t].next)  
      {  
        memcpy(a[pos].data+a[pos].len,a[t].data,a[t].len);  
        a[pos].len+=a[t].len; a[pos].next=a[t].next; delnode(t);  
      }   
    }  
}  
void insert(int pos,int n)  
{  
    int now,i,t;  
    find(pos,now); split(now,pos);  //now记录的是当前位置所在块的编号
    for (i=0;i+blocksize<=n;i+=blocksize){  
        t=newnode();  
        fillnode(t,blocksize,str+i,a[now].next);  
        a[now].next=t;  
        now=t;  
    }  
    if (i<n)  //插入字符的最后一段如果不能填满一整个块就单独处理一下
    {  
        t=newnode();  
        fillnode(t,n-i,str+i,a[now].next);  
        a[now].next=t;  
    }  
    maintain(now);  
}  
void del(int pos,int n)  
{  
    int i,now,t;  
    find(pos,now); split(now,pos);  //删除的时候先处于第一个位置所在的块，通过拆块的方式使当前块中要删除的元素单独分到一个块中
    for (i=a[now].next;i!=-1&&n>a[i].len;i=a[i].next)  n-=a[i].len;  
    split(i,n); i=a[i].next;  
    for(t=a[now].next;t!=i;t=a[now].next) a[now].next=a[t].next,delnode(t);  
    maintain(now);  
}  
void get(int pos,int n)  //将需要输出的元素复制到str数组中
{  
    int i,now,t;  
    find(pos,now); i=min(n,a[now].len-pos);  
    memcpy(str,a[now].data+pos,i);  
    for (t=a[now].next;t!=-1&&i+a[t].len<=n;t=a[t].next)  
     {  
        memcpy(str+i,a[t].data,a[t].len);  
        i+=a[t].len;  
     }  
     if (i<n&&t!=-1)  memcpy(str+i,a[t].data,n-i);  
     str[n]=0;  
}  
void init()    //预处理
{    
    for (int i=1;i<=blocknum;i++)  q.push(i);    
    a[0].len=0; a[0].next=-1;    
}   
void read(int m)  //读入字符串，注意在存储时都是从0开始填
{  
    int i=-1;  
    while (i<m-1)  
    {  
        i++;  
        char c=getchar();  
        str[i]=c;  
        if (c<32||c>126) i--;  
    }  
}   
int main()    
{      
    init();    
    scanf("%d",&n);    
    for (int i=1;i<=n;i++)    
    {    
        scanf("%s",s);    
        if (s[0]=='M')  scanf("%d",&cur); //将光标移动到第K个字符之后   
        if (s[0]=='I') {  //在光标处插入长度为M的字符串  
            scanf("%d",&m);    
            read(m);   
            insert(cur,m);    
        }    
        if (s[0]=='P') cur--;    //光标前移
        if (s[0]=='N') cur++;    //光标后移
        if (s[0]=='D'){    //在光标处删除连续的m个字符
            scanf("%d",&m);    
            del(cur,m);    
        }    
        if (s[0]=='G'){ //输出光标后连续M个字符    
            scanf("%d",&m);    
            get(cur,m);   
            puts(str);   
        }    
    } 
    return 0;
}
