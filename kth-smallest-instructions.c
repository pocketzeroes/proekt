#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;

char*kthSmallestPath(int*destination, int destinationSz, int k){
    ll C[32][32]; clr(C);
    for(int i=0; i<=31; i++){
        C[i][0] = 1;
        for(int j=1; j<=i; j++){
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
    char ret[destination[0] + destination[1]+1]; clr(ret);
    int x = destination[0],
        y = destination[1];
    k--;
    for(int i=0; i < destination[0] + destination[1]; i++){
        if(y-1 >= 0){
            ll num = C[x+y-1][y-1];
            if(k < num){
                ret[i] = 'H';
                y--;
                continue;
            }
            k -= num;
        }
        ret[i] = 'V';
        x--;
    }
    return strdup(ret);
}
