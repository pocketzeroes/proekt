bool isToeplitzMatrix(int**a, int aSz, int*alens){
    int n = aSz, m = alens[0];
    for(int i = 0;i < n-1;i++){
        for(int j = 0;j < m-1;j++){
            if(a[i][j] != a[i+1][j+1])
                return false;
        }
    }
    return true;
}
