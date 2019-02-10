int a_length;
int count(int*a, int K){
    int n = a_length;
    int f[n+1]; memset(f, 0, sizeof(f));
    int dis = 0;
    int p   = 0;
    int ret = 0;
    for(int i = 0; i < n; i++){
        if(++f[a[i]] == 1)
            dis++;
        while(dis > K){
            if(--f[a[p++]] == 0)
                dis--;
        }
        ret += i-p+1;
    }
    return ret;
}
int subarraysWithKDistinct(int*A, int Asz, int K){
    a_length = Asz;
    return count(A, K) - 
           count(A, K-1);
}
