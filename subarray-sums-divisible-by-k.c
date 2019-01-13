enum{ MAXN = 100100};
int kv[MAXN];

int subarraysDivByK(int*A, int Asz, int K){
    for(int i=0; i<K; i++)
        kv[i] = 0;
    int cs = 0;
    kv[0]++;
    for(int i=0; i<Asz; i++){
        int x = A[i];
        cs = (cs + x) % K;
        cs = (cs + K) % K;
        kv[cs]++;
    }
    int ans = 0;
    for(int i=0; i<K; i++)
        ans += (kv[i] * (kv[i] - 1)) / 2;
    return ans;
}
