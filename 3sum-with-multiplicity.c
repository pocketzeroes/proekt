typedef long long ll;
int threeSumMulti(int*A, int Asz, int target){
    int mod = 1000000007;
    int f[101] = {0};
    for(int z=0;z<Asz;z++){int v = A[z];
        f[v]++;
    }
    ll ret = 0;
    for(int i = 0; i <= 100; i++){
        for(int j = i; j <= 100; j++){
            int k = target - i - j;
            if(i <= k && k <= 100){
                if(i < j && j < k){
                    ret += (ll)f[i]*f[j]*f[k];
                }
                else if(i < j && j == k){
                    ret += (ll)f[i]*f[j]*(f[j]-1)/2;
                }
                else if(i == j && j < k){
                    ret += (ll)f[k]*f[j]*(f[j]-1)/2;
                }
                else if(i == j && j == k){
                    ret += (ll)f[i]*(f[i]-1)*(f[i]-2)/6;
                }
            }
        }
    }
    return (int)(ret%mod);
}
