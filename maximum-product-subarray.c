#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int maxProduct(int* A,int Alength) {
    if (Alength == 0) {
        return 0;
    }
    int maxherepre = A[0];
    int minherepre = A[0];
    int maxsofar = A[0];
    int maxhere, minhere;
    for (int i = 1; i < Alength; i++) {
        maxhere    = MAX(MAX(maxherepre * A[i], minherepre * A[i]), A[i]);
        minhere    = MIN(MIN(maxherepre * A[i], minherepre * A[i]), A[i]);
        maxsofar   = MAX(maxhere, maxsofar);
        maxherepre = maxhere;
        minherepre = minhere;
    }
    return maxsofar;
}
