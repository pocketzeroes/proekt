int*sumEvenAfterQueries(int*A, int Asz, int**queries, int queriesSz, int *queries0sz, int*rsz){
    int s = 0;
    for(int z=0;z<Asz;z++){int v = A[z];
        if(v % 2 == 0)
            s += v;
    }
    int q = queriesSz;
    int*ret = calloc(q, sizeof(int));
    for(int i = 0; i < q; i++){
        int d   = queries[i][0];
        int pos = queries[i][1];
        if(A[pos] % 2 == 0)
            s -= A[pos];
        A[pos] += d;
        if(A[pos] % 2 == 0)
            s += A[pos];
        ret[i] = s;
    }
   *rsz = q;
    return ret;
}
