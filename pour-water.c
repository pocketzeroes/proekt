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

enum{ MOD =(int) 1e9+7};
enum{ SIZE =(int) 1e6+10};
int vv[SIZE];

int*pourWater(int*heights, int heightsSz, int V, int K, int*rsz){
    int n = heightsSz;
    for (int i = 0; i < (n); ++i)
        vv[i+1]=heights[i];
    vv[0]=vv[n+1]=MOD;
    while(V--){
        int now=K+1;
        int stop=now;
        for(int i=now;i>0;i--){
            if(vv[i-1]>vv[i])
                break;
            else if(vv[i-1]<vv[i])
                stop=i-1;
        }
        if(stop<now){
            vv[stop]++;
            continue;
        }
        for(int i=now;i<=n;i++){
            if(vv[i+1]>vv[i])
                break;
            else if(vv[i+1]<vv[i])
                stop=i+1;
        }
        vv[stop]++;
    }
    vec res = newVec();
    for(int i = 1; i <= n; ++i)
        res.ptr = pushback(res.ptr, &res.sz, vv[i]);
   *rsz=   res.sz;
    return res.ptr;
}
