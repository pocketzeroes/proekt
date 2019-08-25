typedef struct
{
    int s,t,d;
}edge;
edge e[100005];
int cmpE(const void*pa, const void*pb){
    edge*a=(edge*)pa;
    edge*b=(edge*)pb;
    return(a->d < b->d)?-1:1;
}
int m,f[10005];
int get(int x){
    if(f[x]==x)return x;
    return f[x]=get(f[x]);
}
int minCostToSupplyWater(int n, int*wells, int wellsSz, int**pipes, int pipesSz, int*pipes0sz){
    int ans=0,i;
    for(i=0;i<=n;i++)
        f[i]=i;
    m=pipesSz;
    for(i=0;i<m;i++){
        e[i+1].s=pipes[i][0];
        e[i+1].t=pipes[i][1];
        e[i+1].d=pipes[i][2];
    }
    for(i=0;i<n;i++){
        e[++m].s=0;
        e[m].t=i+1;
        e[m].d=wells[i];
    }
    qsort(e+1, m, sizeof(edge), cmpE);
    for(i=1;i<=m;i++)
        if(get(e[i].s)!=get(e[i].t)){
            f[get(e[i].s)]=get(e[i].t);
            ans+=e[i].d;
        }
    return ans;
}
