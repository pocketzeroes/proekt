int hIndex(int*citations,int n){
    int count[n + 1];
    memset(count,0,sizeof(count));
    for(int i=0;i<n;i++){
        int x=citations[i];
        if (x >= n) 
            ++count[n];
        else 
            ++count[x];
    }
    int h = 0;
    for (int i = n; i >= 0; --i) {
        h += count[i];
        if (h >= i) 
            return i;
    }
    return h;
}

