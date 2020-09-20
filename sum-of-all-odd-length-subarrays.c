int sumOddLengthSubarrays(int*a, int aSz){
    int res = 0;
    int n = aSz;
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            int sum = 0;
            for(int k=i; k<=j; k++){
                sum += a[k];
            }
            if((j - i + 1) % 2 == 1)
                res += sum;
        }
    }
    return res;
}
