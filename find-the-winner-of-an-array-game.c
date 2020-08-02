int getWinner(int*arr, int arrSz, int k){
    int n = arrSz;
    k = fmin(k, n);
    int A = arr[0];
    int rep = 0;
    for(int i = 1;;i++){
        int B = arr[i%n];
        if(A >= B){
            rep++;
        }
        else{
            A = B;
            rep = 1;
        }
        if(rep == k){
            return A;
        }
    }
}
