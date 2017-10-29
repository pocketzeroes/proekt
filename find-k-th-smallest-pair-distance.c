int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int smallestDistancePair(int*a, int aSz, int k){
    int n = aSz;
    qsort(a,aSz,sizeof(int),cmp);
    k--;
    int low = -1, high = 100000000;
    while(high - low > 1){
        int h = high+low>>1;
        int ct = 0;
        int p = 0;
        for(int i = 0;i < n;i++){
            while(p < i && a[i] - a[p] > h){
                p++;
            }
            ct += i-p;
        }
        if(k < ct){
            high = h;
        }
        else{
            low = h;
        }
    }
    return high;
}
