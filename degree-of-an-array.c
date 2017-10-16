void Max(int*a, int b){
    if(*a<b)
       *a=b;
}
void Min(int*a, int b){
    if(*a>b)
       *a=b;
}

int c[50010],
    l[50010],
    r[50010];

int findShortestSubArray(int*a, int aSz){
    int n = aSz;
    for(int i=0;i<50010;i++)
        c[i]=0,l[i]=-1;
    for(int i=0;i<n;i++){
        int first=a[i];
        if( l[first]==-1)
            l[first]=i;
        c[first]++;
        r[first]=i;
    }
    int mx=0,ans=n;
    for(int i=0;i<50010;i++)
        if(l[i]>=0)
            Max(mx,c[i]);
    for(int i=0;i<50010;i++){
        if(c[i]==mx)
            Min(ans,r[i]-l[i]+1);
    }
    return ans;
}

