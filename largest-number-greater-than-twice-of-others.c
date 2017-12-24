int dominantIndex(int*a, int aSz){
    int n = aSz;
    for(int i = 0; i < n; ++i){
        bool ok = true;
        for(int j = 0; j < n; ++j)
            if(j != i && a[i] < a[j] * 2)
                ok = false;
        if(ok)
            return i;
    }
    return -1;
}
