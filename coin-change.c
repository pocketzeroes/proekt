int coinChange(int* c, int aS, int N) {
    int i, j, *a;
    if(N == 0) return 0;
    a = malloc(sizeof(int)*(N+1));
    a[0] = 0;
    for(i=1; i<=N; i++)
    {
        a[i] = 0;
        for(j=0; j<aS; j++)
        {
            if(c[j] > i)		
                continue;
            else if(i==c[j])	
            {
                a[i] = 1;
                break;
            }
            else if(a[i-c[j]] == 0)	
                continue;   
            if(a[i])	
                a[i] = a[i] > a[i-c[j]]+1 ? a[i-c[j]]+1 : a[i];
            else
                a[i] = a[i-c[j]]+1;
        }
    }
    i = a[N] ? a[N] : -1;
    free(a);
    return i;
}