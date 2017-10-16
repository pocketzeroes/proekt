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

int unique(int *a, int len)
{
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j]) a[++j] = a[i];
	return j + 1;
}

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

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

/////
void Max(int*a, int b){
    if(*a<b)
       *a=b;
}
int*fallingSquares(int**a, int aSz, int a0sz, int*rsz){
    int n=aSz, ans=0;
    vec first = newVec();
    vec res   = newVec();
    for(int i=0; i<n; i++){
        first.ptr =pushback(first.ptr, &first.sz, a[i][0]);
        first.ptr =pushback(first.ptr, &first.sz, a[i][0]+a[i][1]);
    }
    qsort(first.ptr, first.sz, sizeof(int), cmp);
    int fsz = unique(first.ptr, first.sz);
    first.sz = fsz;
    int d[fsz]; memset(d, 0, sizeof(d));
    for(int i=0; i<n; i++){
        int l = lower_bound(first.ptr, first.sz, a[i][0]);
        int r = lower_bound(first.ptr, first.sz, a[i][0]+a[i][1]);
        int mx=0;
        for(int j=l; j<r; j++)
            Max(&mx, d[j]);
        mx += a[i][1];
        for(int j=l; j<r; j++)
            d[j] = mx;
        Max(&ans, mx);
        res.ptr = pushback(res.ptr, &res.sz, ans);
    }
   *rsz =  res.sz;
    return res.ptr;
}





























