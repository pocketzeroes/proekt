int min(int a,int b){return a<b?a:b;}
typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value) {
    ll*output = resizeArray(array, ll, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    ll*ptr;
    int sz;
}vecl;
vecl newVecL(){
    vecl rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}
int *pushback(int *array, int *size, int value){
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int leastOpsExpressTarget(int x, int target){
    vecl p = newVecL();
    vec  b = newVec();
    ll t=1, n=target;
    while(n>0){
        b.ptr = pushback(b.ptr, &b.sz, n%x);
        n /= x;
        p.ptr = pushbackL(p.ptr, &p.sz, t);
        t *= x;
    }
    p.ptr=pushbackL(p.ptr, &p.sz, t);
    b.ptr=pushback (b.ptr, &b.sz, 0);
    int m = p.sz;
    int dp[m][2];
    dp[0][0] = b.ptr[0] * 2;
    dp[0][1] = (x-b.ptr[0]) * 2;
    for (int i = 1; i < m; i++){
        dp[i][0] = min(b.ptr[i]*i + dp[i-1][0], (b.ptr[i]+1)*i + dp[i-1][1]);
        dp[i][1] = min((x-b.ptr[i])*i + dp[i-1][0], (x-b.ptr[i]-1)*i + dp[i-1][1]);
    }
    int ans = min(dp[m-1][0]-1, dp[m-1][1]+m-1);
    return ans;
}
