typedef struct Point P;
P newPoint(int a, int b){
    P rez;
    rez.x = a;
    rez.y = b;
    return rez;
}
int cmpP(const void*pa, const void*pb){
    P*a=(P*)pa;
    P*b=(P*)pb;
    int diff;
    diff = a->x - b->x;  if(diff!=0) return diff;
    return a->y - b->y;
}
P operatorSub(P a, P b){
    return newPoint(a.x-b.x, a.y-b.y);
}
int operatorMul(P a, P b){ 
    return a.x*b.y - b.x*a.y; 
}
int X(P o, P a, P b){ 
    return operatorMul(operatorSub(a,o), operatorSub(b,o)); 
}

P*outerTrees(P*p,int pSz,int*retSz){
    int n=pSz;
    qsort(p, pSz, sizeof(P), cmpP);
    int m1=0, m2=0;
    P q1[n], q2[n];
    for ( int i=0; i<n; i++ ){
        while ( m1>=2 && X(q1[m1-2], q1[m1-1],p[i])>0 ) m1--;
        while ( m2>=2 && X(q2[m2-2], q2[m2-1],p[i])<0 ) m2--;
        q1[m1++] = q2[m2++] = p[i];
    }
    n=0;
    for ( int i=0; i<m1; i++ ) 
        p[n++]=q1[i];
    if ( n<pSz ) {
        for ( int i=m2-2; i>=1; i-- ) 
            p[n++]=q2[i];
    }
    *retSz=n;
    return p;
}
