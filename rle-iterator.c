typedef struct {
}RLEIterator;
RLEIterator*gptr;
int min(int a,int b){return a<b?a:b;}

int*a;
int aSz;
int p = 0;

RLEIterator*rLEIteratorCreate(int*A){
    int i;
    for(i=0; !(A[i+1]==0&&
               A[i+2]==0); i++){
        printf("[%d] ", A[i]);
    }
    aSz=i;
    a = A;
    p = 0;
    return gptr;
}
int rLEIteratorNext(RLEIterator*obj, int n){
    if(p >= aSz)
        return -1;
    n--;
    int ret = -1;
    while(n > 0){
        if(p >= aSz)
            return -1;
        int ex = min(a[p], n);
        n -= ex;
        a[p] -= ex;
        if(a[p] > 0)
            break;
        else
            p += 2;
    }
    while(p < aSz && a[p] == 0)
        p += 2;
    if(p < aSz)
        ret = a[p+1];
    n = 1;
    while(n > 0){
        if(p >= aSz)
            return -1;
        int ex = min(a[p], n);
        n -= ex;
        a[p] -= ex;
        if(n == 0)
            break;
        p += 2;
    }
    return ret;
}
void rLEIteratorFree(RLEIterator* obj){
    return;
}
