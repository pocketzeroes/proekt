char*prepend(char*s, int v){
  char*ptr=NULL;
  asprintf(&ptr, "%d%s", v, s);
  return ptr;
}

int asz;
int*decimal(int n, int K){
    int*a = calloc(100, sizeof(int));
    int AK = abs(K);
    int p = 0;
    while(n != 0){
        int d = (n%AK+AK)%AK;
        a[p++] = d;
        n = (n-d)/K;
    }
    if(p == 0)
        p++;
    asz=p;
    return a;
}
char*baseNeg2(int N){
    int*d = decimal(N, -2);
    char*ret = strdup("");
    for(int i=0;i<asz;i++){int v = d[i];
        ret = prepend(ret, v);
    }
    return ret;
}
