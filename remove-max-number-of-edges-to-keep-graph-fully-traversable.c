enum{maxn = 100005};
int par [maxn],
    par2[maxn];

int find(int x){
    if(x==par[x])
        return x;
    else{
        par[x]=find(par[x]);
        return par[x];
    }
}
int find2(int x){
    if(x==par2[x])
        return x;
    else{
        par2[x]=find2(par2[x]);
        return par2[x];
    }
}
int maxNumEdgesToRemove(int n, int**es, int esSz, int*es0sz){
    for(int i=1;i<=n;++i)
        par[i]=par2[i]=i;
    int ans=0;
    for(int z=0;z<esSz;z++){int*V=es[z];
        int u=V[1],v=V[2],t=V[0];
        if(t != 3)
            continue;
        if(find2(u) == find2(v) || find(u) == find(v))
            continue;
        par[find(u)] = find(v);
        par2[find2(u)] = find2(v);
        ++ans;
    }
    for(int z=0;z<esSz;z++){int*V=es[z];
        int u=V[1],v=V[2],t=V[0];
        if(t == 3)
            continue;
        if(t == 1){
            int x=find(u),y=find(v);
            if(x == y)
                continue;
            par[find(u)] = find(v);
            ++ans;
        }
        else if(t == 2) {
            if(find2(u) == find2(v))
                continue;
            par2[find2(u)] = find2(v);
            ++ans;
        }
    }
    int c1=0,c2=0;
    for(int i=1;i<=n;++i){
        if(find(i)==i)
            c1++;
        if(find2(i)==i)
            c2++;
    }
    if(c1 > 1 || c2 > 1)
        return-1;
    return esSz - ans;
}
