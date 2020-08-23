#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
enum{ maxn=100005};
int par[maxn],
    sz [maxn],
    b  [maxn];
int cnt[maxn];

int find(int x){
    if(x==par[x])
        return x;
    else{
        par[x]=find(par[x]);
        return par[x];
    }
}

void merge(int x,int y){
    int a=find(x),b=find(y);
    if(a!=b) {
        cnt[sz[a]]--;
        cnt[sz[b]]--;
        par[a]=b;
        sz[b]+=sz[a];
        cnt[sz[b]]++;
    }
}
int findLatestStep(int*a, int aSz, int m){
    clr(par);
    clr(sz );
    clr(b  );
    clr(cnt);
    int n=aSz;
    for(int i=1;i<=n;++i)
        par[i]=i,sz[i]=1;
    int ret=0,tp=1;
    for(int z=0;z<aSz;z++){int i=a[z];
        b[i]=1;
        cnt[1]++;
        if(b[i-1]){
            merge(i,i-1);
        }
        if(b[i+1]){
            merge(i,i+1);
        }
        if(cnt[m])
            ret=tp;
        ++tp;
    }
    if(!ret)
        return -1;
    return ret;
}
