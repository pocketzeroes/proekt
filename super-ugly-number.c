int nthSuperUglyNumber(int n, int *P, int pS) {
    int i, j, min;
    int u[1000000], last[100]={0,};
    u[0] = 1;
    for(i=1; i<n; i++)
    {
        u[i] = u[last[0]]*P[0];
        for(j=1; j<pS; j++)
        {
            min = P[j]*u[last[j]];
            u[i] = u[i]<min ? u[i]:min ;
        }
        for(j=0; j<pS; j++)
            if(u[i] == P[j]*u[last[j]])
                last[j]++;
    }
    min = u[n-1];
    return min;
}
