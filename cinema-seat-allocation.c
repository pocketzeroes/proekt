int cmp(const void*pa, const void*pb){
    int**aa=(int**)pa;
    int**bb=(int**)pb;
    int*a = *aa;
    int*b = *bb;
    if(a[0] != b[0])
        return a[0] - b[0];
    return a[1] - b[1];
}
int maxNumberOfFamilies(int n, int**reservedSeats, int reservedSeatsSz, int*reservedSeats0sz){
    qsort(reservedSeats, reservedSeatsSz, sizeof(int*), cmp);
    int ret = 2*n;
    for(int i = 0; i < reservedSeatsSz;){
        int j = i;
        while(j < reservedSeatsSz && reservedSeats[j][0] == reservedSeats[i][0])
            j++;
        ret -= 2;
        int ptn = 0;
        for(int k = i;k < j;k++)
            ptn |= 1<<reservedSeats[k][1];
        if((ptn&((1<<10)-(1<<2))) == 0)
            ret += 2;
        else if((ptn&((1<<8)-(1<<4))) == 0)
            ret++;
        else if((ptn&((1<<6)-(1<<2))) == 0)
            ret++;
        else if((ptn&((1<<10)-(1<<6))) == 0)
            ret++;
        i = j;
    }
    return ret;
}
