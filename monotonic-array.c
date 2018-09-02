bool isMonotonic(int*A, int Asz){
    int ok=1, ok2=1;
    for(int i=1; i<Asz; i++){
        if(A[i]<A[i-1])
            ok=0;
        if(A[i]>A[i-1])
            ok2=0;
    }
    return ok|ok2;
}
