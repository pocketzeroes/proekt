int f[65536];
int work(int n){
    if(n<65536)
        return f[n];
    return fmin(work(n>>1)+(n&1)+1,work(n/3)+n%3+1);
}
int minDays(int n){
    int i;
    for(i=1;i<65536;i++){
        f[i]=f[i-1];
        if(!(i&1))
            f[i]=fmin(f[i],f[i>>1]);
        if(!(i%3))
            f[i]=fmin(f[i],f[i/3]);
        f[i]++;
    }
    return work(n);
}
