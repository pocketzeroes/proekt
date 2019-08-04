int movesToMakeZigzag(int*nums, int numsSz){
    int n = numsSz, i, j, s=0, t=0;
    for(i=0; i<n; i+=2){
        j=0;
        if(i)
            j=fmax(j,nums[i]-nums[i-1]+1);
        if(i+1<n)
            j=fmax(j,nums[i]-nums[i+1]+1);
        s+=j;
    }
    for(i=1;i<n;i+=2){
        j=0;
        if(i)
            j=fmax(j,nums[i]-nums[i-1]+1);
        if(i+1<n)
            j=fmax(j,nums[i]-nums[i+1]+1);
        t+=j;
    }
    return fmin(s,t);
}
