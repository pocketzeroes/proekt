int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
int unique(int*a, int len){
	int i, j;
	for(i = j = 0; i < len; i++)
		if (a[i] != a[j])
          a[++j] = a[i];
	return j + 1;
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
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
int lower_bound(int*a, int n, int x){
  int l = 0;
  int h = n;
  while (l < h){
    int mid = (l + h) / 2;
    if (x <= a[mid]) 
      h = mid;
    else
      l = mid + 1;
  }
  return l;
}


int ok[4020];
int dp[2020][4020];

int makeArrayIncreasing(int*arr1, int arr1sz, int*arr2, int arr2sz){
        vec V=newVec();
        pb(V,-1);
        for(int z=0;z<arr1sz;z++){int v=arr1[z];
            pb(V, v);
        }
        for(int z=0;z<arr2sz;z++){int v=arr2[z];
            pb(V, v);
        }
        qsort(V.ptr, V.sz, sizeof(int), cmp);
        V.sz=unique(V.ptr, V.sz);
        for(int z=0;z<arr1sz;z++){
            #define v arr1[z]
            v = lower_bound(V.ptr, V.sz, v);
            #undef v
        }
        memset(ok,0,sizeof(ok));
        for(int z=0;z<arr2sz;z++){int v=arr2[z];
            ok[lower_bound(V.ptr, V.sz, v)]=1;
        }
        int x,y;
        for(x=0;x<(2010);x++) 
            for(y=0;y<(4010);y++)
                dp[x][y]=1010101;
        dp[0][0]=0;
        for(x=0;x<arr1sz;x++){
            int mi=1010101;
            for(y=0;y<10;y++)
                for(y=0;y<(4010);y++){
                    if(arr1[x]==y)
                        dp[x+1][y]=fmin(dp[x+1][y],mi);
                    if(ok[y])
                        dp[x+1][y]=fmin(dp[x+1][y],mi+1);
                    mi=fmin(mi,dp[x][y]);
                }
        }
    int ret=101010;
    for(y=0;y<(4010);y++)
        ret=fmin(ret,dp[arr1sz][y]);
    if(ret>101000)
        ret=-1;
    return ret;
}
