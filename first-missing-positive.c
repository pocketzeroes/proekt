int firstMissingPositive(int*A,int Alength) {
    int i=0;
    void swap(int*A,int a,int j ){
        int temp = A[i];
        A[a] = A[j];
        A[j] = temp;
    }
    while(i < Alength){
        if(A[i] == i+1 || A[i] <= 0 || A[i] > Alength) i++;
        else if(A[A[i]-1] != A[i]) swap(A, i, A[i]-1);
        else i++;
    }
    i = 0;
    while(i < Alength && A[i] == i+1) i++;
    return i+1;
}
