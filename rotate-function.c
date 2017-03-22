inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int maxRotateFunction(int*A,int Asize) {
    int sum=0;
    for(int i=0;i<Asize;i++)
        sum+=A[i];
    int fi = 0;
    for (int i = 0; i < Asize; ++i) 
        fi += i * A[i];
    int result = fi;
    for (int i = 1; i <= Asize; ++i) {
        fi += sum - Asize * A[Asize - i];
        result = max(result, fi);
    }
    return result;
}
