int specialArray(int*a, int aSz){
    int n = aSz;
    for(int x=0; x<=n; ++x){
        int cnt=0;
        for(int z=0;z<aSz;z++){int i=a[z];
            if(i>=x)
                ++cnt;
        }
        if(cnt == x)
            return x;
    }
    return-1;
}
