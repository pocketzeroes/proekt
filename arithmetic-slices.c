int numberOfArithmeticSlices(int*A,int Asize){
    int res = 0, i = 0;
    for (int i = 0; i + 2 < Asize; ++i) {
        int start = i;
        while (i + 2 < Asize && A[i + 2] + A[i] == 2 * A[i + 1]) {
            res += (i++) - start + 1;
        }
    }
    return res;
}
     