typedef long long ll;
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}

ll power(ll x){
    int s = 0;
    while(x != 1){
        if(x % 2 == 0)
            x /= 2;
        else
            x = x * 3 + 1;
        s++;
    }
    return s;
}
int getKth(int lo, int hi, int k){
    int lsz = hi-lo+1;
    ll list[lsz];
    int l=0;
    for(int i=lo; i<=hi; i++)
        list[l++]=power(i)<<32|i;
    qsort(list, lsz, sizeof(ll), cmpLL);
    return list[k-1];
}
