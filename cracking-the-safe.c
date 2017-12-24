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

char*concat(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c", a, b);
  return ptr;
}


vec ret;
int*a;
int n, k;
void db(int t, int p) {
    if (t > n) {
        if (n % p == 0) {
            for (int k = 1; k <= p; ++k)
                ret.ptr = pushback(ret.ptr, &ret.sz, a[k]);
        }
        return;
    }
    a[t] = a[t - p];
    db(t + 1, p);
    for (int j = a[t - p] + 1; j < k; ++j) {
        a[t] = j;
        db(t + 1, t);
    }
}
char*crackSafe(int pn, int pk){
    ret=newVec();
    n = pn;
    k = pk;
    a = calloc(k*n, sizeof(int));
    ret.sz = 0;
    db(1, 1);
    char*ans = strdup("");
    for(int z=0;z<ret.sz;z++){int it = ret.ptr[z];
        ans = concat(ans, '0'+it);
    }
    for(int i = 0; i < n - 1; ++i){
        ans = concat(ans, '0'+ret.ptr[i]);
    }
    return ans;
}
