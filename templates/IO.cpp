namespace IO
{
	const unsigned int bufsize=1<<16,outsize=1<<20;
	static char ch[bufsize],*S=ch,*T=ch;
	inline char getc()
	{return ((S==T)&&(T=(S=ch)+fread(ch,1,bufsize,stdin),S==T)?0:*S++);}
	static char Out[outsize],*nowp=Out;
	inline void flush(){fwrite(Out,1,nowp-Out,stdout);nowp=Out;}
	template<typename T>
		void read(T &x)
		{
			char c=getc();x=0;
			for(;!isdigit(c);c=getc());
			for(;isdigit(c);x=(x<<1)+(x<<3)+(c^'0'),c=getc());
		}
	void readstr(char *s)
	{
		char c=getc();static int slen=0;
		f(i,1,slen)s[i]=0;slen=0;
		for(;!isalpha(c);c=getc());
		for(;isalpha(c);c=getc())s[++slen]=c;
	}
	template<typename T>
		void write(T x,char c='\n')
		{
			if(!x)*nowp++='0';
			if(x<0)*nowp++='-',x=-x;
			static unsigned int stk[50],tp=0;
			for(;x;x/=10)stk[++tp]=x%10;
			for(;tp;*nowp++=stk[tp--]^'0');*nowp++=c;
		}
}
