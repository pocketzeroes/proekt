#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///
enum{ INF = 1 << 30};

int* cheapestJump(int*a, int asize, int B, int*rsz){
    int n = asize;
    int dp  [n];
    int path[n];
    dp[n - 1] = 0;
    for(int i = n - 2; i >= 0; --i){
        dp[i] = INF;
        if (a[i] < 0) 
            continue;
        for (int j = 1; j <= B && i + j < n; ++j) {
            if (a[i + j] < 0) 
                continue;
            if (dp[i + j] + a[i] < dp[i]){
                dp[i] = dp[i + j] + a[i];
                path[i] = i + j;
            }
        }
    }
    vec ret=newVec();
    if (dp[0] == INF) 
        goto fin;
    ret.ptr = pushback(ret.ptr, &ret.sz ,1);
    int cur = 0;
    while(cur != n - 1){
        ret.ptr = pushback(ret.ptr, &ret.sz ,path[cur] + 1);
        cur = path[cur];
    }
 fin:
   *rsz=   ret.sz;
    return ret.ptr;
}













































