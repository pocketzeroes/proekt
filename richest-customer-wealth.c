int maximumWealth(int**accounts, int accountsSz, int*accounts0sz){
    int max = 0;
    for(int z=0; z<accountsSz; z++){int*row = accounts[z];
        int s = 0;
        for(int q=0;q<accounts0sz[z];q++){int v=row[q];
            s += v;
        }
        max = fmax(max, s);
    }
    return max;
}
