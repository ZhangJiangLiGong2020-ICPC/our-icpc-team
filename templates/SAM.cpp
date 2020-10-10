namespace SAM
{
    int cnt=0,las=0,cur;
    void extend(char *s,int n)
    {
        int p,q,clone,x;
        link[0]=-1;
        f(i,1,n)
        {
            x=s[i]-'a';
            cur=++cnt,len[cur]=len[las]+1,res[cur]=num[n-i+2];
            for(p=las;p!=-1&&(!nex[p][x]);p=link[p])nex[p][x]=cur;
            if(p==-1)link[cur]=0;
            else
            {
                q=nex[p][x];
                if(len[q]==len[p]+1)link[cur]=q;
                else
                {
                    clone=++cnt,len[clone]=len[p]+1;
					link[clone]=link[q];
                    memcpy(nex[clone],nex[q],sizeof nex[q]);
                    for(;p!=-1&&(nex[p][x]==q);p=link[p])nex[p][x]=clone;
                    link[cur]=link[q]=clone;
                }
            }las=cur;
        }
    }
	void linktree()
	{
		f(i,0,cnt)vec[len[i]].pb(i);
		rf(i,neko-5,1)for(int x:vec[i])res[link[x]]+=res[x];
	}
}
