int m,h[10005],ne[20005],p[20005],f[10005],d[10005];
void dfs(int x)
{
    for(int i=h[x];i;i=ne[i])if(p[i]!=f[x])
    {
        f[p[i]]=x;
        d[p[i]]=d[x]+1;
        dfs(p[i]);
    }
}
int treeDiameter(int**edges, int edgesSz, int*edges0sz){
    int n=edgesSz+1,i,j;
    m=0;
    memset(h,0,sizeof(h));
    for(int z=0;z<edgesSz;z++){int*e=edges[z];
        p[++m]=e[1];
        ne[m]=h[e[0]];
        h[e[0]]=m;
        p[++m]=e[0];
        ne[m]=h[e[1]];
        h[e[1]]=m;
    }
    d[0]=0;
    f[0]=-1;
    dfs(0);
    for(i=j=0;i<n;i++)if(d[i]>d[j])j=i;
    d[j]=0;
    f[j]=-1;
    dfs(j);
    for(i=j=0;i<n;i++)if(d[i]>d[j])j=i;
    return d[j];
}
