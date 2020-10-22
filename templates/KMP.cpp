#include<cstdio>
#include<cstring>
#define f(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;i=-(~i))
int nex[1000010],n;
void getborder(char *s)
{
	int n=strlen(s+1);
	nex[0]=-1;
	f(i,2,n)
	{
		int x=nex[i-1];
		while(x!=-1)
		{if(s[x+1]==s[i]){nex[i]=x+1;break;}x=nex[x];}
	}
}
char s[1000010],t[1000010];
int main()
{
	scanf("%s%s",s+1,t+1);
	int n=strlen(s+1),m=strlen(t+1);
	getborder(t);
	int x=0;
	f(i,1,n)
	{
		while(x&&t[x+1]^s[i])x=nex[x];
		++x;
		if(x==m)printf("%d\n",i-m+1);
	}
	f(i,1,m)printf("%d%c",nex[i],i^iend?' ':'\n');
}
