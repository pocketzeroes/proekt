void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int*ans;
int m,h[100005],ne[200005],p[200005],a[100005],d[100005],f[100005],s[55],g[55][55];

void dfs(int x){
    int i,t;
    for(i=1;i<51;i++)if(~s[i]&&g[a[x]][a[s[i]]]==1&&(!~ans[x]||d[ans[x]]<d[s[i]]))ans[x]=s[i];
    t=s[a[x]];
    s[a[x]]=x;
    for(i=h[x];i;i=ne[i])if(p[i]!=f[x]){
        f[p[i]]=x;
        d[p[i]]=d[x]+1;
        dfs(p[i]);
    }
    s[a[x]]=t;
}
int*getCoprimes(int*nums, int numsSz, int**edges, int edgesSz, int*edges0sz, int*rsz){
    int n=numsSz,i,j;
    m=0;
    fill(h, n, 0);
    for(i=0;i+1<n;i++){
        p[++m]=edges[i][1];
        ne[m]=h[edges[i][0]];
        h[edges[i][0]]=m;
        p[++m]=edges[i][0];
        ne[m]=h[edges[i][1]];
        h[edges[i][1]]=m;
    }
    for(i=0;i<n;i++)a[i]=nums[i];
    for(i=0;i<51;i++)g[0][i]=g[i][0]=i;
    for(i=1;i<51;i++)for(j=1;j<=i;j++)g[i][j]=g[j][i]=g[j][i%j];
    f[0]=d[0]=0;
    memset(s,-1,sizeof(s));
    ans=calloc(n, sizeof(int));
    fill(ans, n, -1);
    dfs(0);
   *rsz=n;
    return ans;
}
