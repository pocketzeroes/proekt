int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int unique(int *a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}
int lower_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}

typedef long long ll;
enum{ MOD =(int) 1e9 + 7};

int rectangleArea(int**a, int aSz, int*a0sz){
    int n = aSz;
    vec X = newVec();
    vec Y = newVec();
    for(int i=0; i<n; ++i){
        X.ptr=pushback(X.ptr, &X.sz, a[i][0]);
        X.ptr=pushback(X.ptr, &X.sz, a[i][2]);
        Y.ptr=pushback(Y.ptr, &Y.sz, a[i][1]);
        Y.ptr=pushback(Y.ptr, &Y.sz, a[i][3]);
    }
    qsort(X.ptr, X.sz, sizeof(int), cmp);
    X.sz = unique(X.ptr, X.sz);
    qsort(Y.ptr, Y.sz, sizeof(int), cmp);
    Y.sz = unique(Y.ptr, Y.sz);
    bool visit[X.sz][Y.sz];
    for(int i=0; i<X.sz; i++)
      for(int j=0; j<Y.sz; j++)
        visit[i][j] = 0;
    
    for(int i=0; i<n; ++i){
        int x1 = lower_bound(X.ptr, X.sz, a[i][0]);
        int x2 = lower_bound(X.ptr, X.sz, a[i][2]);
        int y1 = lower_bound(Y.ptr, Y.sz, a[i][1]);
        int y2 = lower_bound(Y.ptr, Y.sz, a[i][3]);
        for (int u = x1; u < x2; ++u)
            for (int v = y1; v < y2; ++v)
                visit[u][v] = true;
    }
    int ret = 0;
    for(int i = 0; i < X.sz; ++i)
        for(int j = 0; j < Y.sz; ++j)
            if(visit[i][j])
                ret = (ret + (ll)(X.ptr[i + 1] - X.ptr[i]) * (Y.ptr[j + 1] - Y.ptr[j])) % MOD;
    return ret;
}
