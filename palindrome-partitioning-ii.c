#define MIN(a,b) (((a)<(b))?(a):(b))
int minCut(char* s) {
    int N = strlen(s);
    if(N<=1) return 0;
    int i, j, minCUTS[N+1];
    for(i=0; i<=N; ++i) minCUTS[i] = i-1;
    for(i=1;i<N;i++)
    {
        for(j=0;(i-j)>=0 && (i+j)<N && s[i-j]== s[i+j]; ++j) 
            minCUTS[i+j+1] = MIN(minCUTS[i+j+1], 1 + minCUTS[i-j]);
        for(j=0;(i-j-1)>=0 && (i+j)<N && s[i-j-1]== s[i+j]; ++j) 
            minCUTS[i+j+1] = MIN(minCUTS[i+j+1], 1 + minCUTS[i-j-1]);
    }
    return minCUTS[N];
}
