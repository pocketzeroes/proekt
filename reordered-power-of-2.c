bool reorderedPowerOf2(int N) {
    int ten [10] = {0}; 
    int ten1[10] = {0};
    int k = 0;
    do
      ten[N%10]++;
    while(N /= 10);
    for(long m = 1L<<31; m; m >>= 1){
        memcpy(ten1, ten, 10*sizeof(int));
        long t = m;
        do
          ten1[t%10]--;
        while(t /= 10);
        int cnt=0;
        for(int i=0;i<10;i++)
            if(ten1[i]==0)
                cnt++;
        if(cnt == 10)
            return true;
    }
    return false;
}
