int*processQueries(int*queries, int queriesSz, int m, int*rsz){
    int a[m];
    for(int i=0; i<m; i++)
        a[i] = i+1;
    int*ret = calloc(queriesSz, sizeof(int));
    for(int i=0; i<queriesSz; i++){
        int q = queries[i];
        for(int j=0; j<m; j++){
            if(a[j] == q){
                ret[i] = j;
                for(int k=j; k>=1; k--)
                    a[k] = a[k-1];
                a[0] = q;
                break;
            }
        }
    }
   *rsz=queriesSz;
    return ret;
}
