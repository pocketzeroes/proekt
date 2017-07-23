int* findErrorNums(int*nums, int numsSz, int*rsz){
    int n = numsSz;
    int cnt[n + 1];
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<numsSz;i++){int x = nums[i];
        cnt[x]++;
    }
    int a, b;
    for(int i = 1; i <= n; i++) 
        if(cnt[i] == 2)
            a = i;
    else if(cnt[i] == 0) 
        b = i;
    int*rv=malloc(2*sizeof(int));
   *rsz=2;
    rv[0]=a;
    rv[1]=b;
    return rv;
}
