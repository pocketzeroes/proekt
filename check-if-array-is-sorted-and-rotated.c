bool check(int*a, int aSz){
    int n = aSz;
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1; j++){
            if(a[(i+j) % n] > a[(i+j+1) % n])
              goto outer;
        }
        return true;
    outer:;
    }
    return false;
}
