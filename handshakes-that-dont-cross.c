#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;

int numberOfWays(int n){
    ll catalan[n/2+2]; clr(catalan);
    catalan[0] = 1;
    catalan[1] = 1;
    for(int i=2; i<=n/2; i++){
        catalan[i] = 0;
        for(int j=0; j<i; j++)
            catalan[i] = (catalan[i] + catalan[j] * catalan[i - j - 1] % 1000000007) % 1000000007;
    }
    return(int)catalan[n/2];
}
