int maxScore(int*p, int pSz, int k){
    int su=0,mx=0,s=pSz;
    for(int i=0;i<k;++i)
        su+=p[i];
    mx = fmax(mx,su);
    for(int i=0;i<k;++i){
        su-=p[k-i-1];
        su+=p[s-i-1];
        mx=fmax(mx,su);
    }
    return mx;
}
